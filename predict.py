import argparse

import cv2
import numpy as np
import tensorflow as tf
from keras.models import load_model

from src.data_structures import Point, Rect

IMAGE_SIZE = (160, 160)
MODEL_FACE_DETECTOR = "resources/models/face_detector.pb"
MODEL_ICAONET = "resources/models/icaonet.h5"


def load_graph_from_pb(pb_file):
    graph = tf.Graph()
    graph_def = tf.GraphDef()
    graph_def.ParseFromString(open(pb_file, "rb").read())

    with graph.as_default():
        tf.import_graph_def(graph_def)
    return graph


def run_graph(graph, inputs_list, input_tensor_names, output_tensor_names):
    assert len(inputs_list) == len(input_tensor_names)

    with tf.Session(graph=graph) as sess:
        input_tensors = [graph.get_tensor_by_name(name) for name in input_tensor_names]
        output_tensors = [
            graph.get_tensor_by_name(name) for name in output_tensor_names
        ]
        feed_dict = {tensor: value for tensor, value in zip(input_tensors, inputs_list)}
        return sess.run(output_tensors, feed_dict=feed_dict)


def run_face_detector(bgr_image):
    face_detector = load_graph_from_pb(MODEL_FACE_DETECTOR)

    img = cv2.cvtColor(bgr_image, cv2.COLOR_BGR2RGB)
    img = img.astype(np.uint8)
    height, width = img.shape[:2]

    inputs_list = [np.expand_dims(img, axis=0)]
    input_tensor_names = ["import/image_tensor:0"]
    output_tensor_names = ["import/detection_boxes:0", "import/detection_scores:0"]
    boxes, scores = run_graph(
        face_detector, inputs_list, input_tensor_names, output_tensor_names
    )

    best_rect = boxes.squeeze()[scores.squeeze().argmax()]
    best_rect = best_rect * [height, width, height, width]
    best_rect = best_rect.astype(np.int)
    y1, x1, y2, x2 = best_rect
    return Rect.from_tl_br_points((x1, y1), (x2, y2))


def preprocessing(bgr_image):
    face_rect = run_face_detector(bgr_image)
    w, h = face_rect.width, face_rect.height

    pad_rect = Rect(face_rect.x, face_rect.y, w + int(w * 1.5), h + int(h * 1.5))
    pad_rect.height = pad_rect.width = max(pad_rect.height, pad_rect.width)

    center_pad = Point(
        (pad_rect.x + pad_rect.width) // 2, (pad_rect.y + pad_rect.height) // 2
    )
    center_face = Point(
        (face_rect.x + face_rect.width) // 2, (face_rect.y + face_rect.height) // 2
    )
    offset_center = Point(center_face.x - center_pad.x, center_face.y - center_pad.y)
    pad_rect += offset_center

    im_h, im_w = bgr_image.shape[:2]
    br_x, br_y = pad_rect.br()
    left = abs(min(0, pad_rect.x))
    top = abs(min(0, pad_rect.y))
    right = 0 if br_x < im_w else br_x - im_w
    bottom = 0 if br_y < im_h else br_y - im_h

    im_res = cv2.copyMakeBorder(
        bgr_image, top, bottom, left, right, cv2.BORDER_CONSTANT, value=0
    )
    pad_rect.x += left
    pad_rect.y += top

    l, t = pad_rect.tl()
    r, b = pad_rect.br()
    return im_res[t:b, l:r]


def run_icaonet(filepath):
    im = cv2.imread(filepath, cv2.IMREAD_ANYCOLOR)
    im = preprocessing(im)
    im = cv2.resize(im, IMAGE_SIZE, interpolation=cv2.INTER_AREA).astype(np.float32)
    im = np.expand_dims(im, axis=0)

    model = load_model(MODEL_ICAONET)
    return model.predict(im / 255)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filepath")
    args = parser.parse_args()

    y_pred = run_icaonet(args.filepath)
    print(y_pred)
