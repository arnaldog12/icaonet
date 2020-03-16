import cv2
import numpy as np
from glob import glob
from os import path
from mrk_file import MRKFile
from sys import stdout

def images_from_folder(folder_path, output_size=None, output_type=np.float32, bgr2rgb=False, interpolation=cv2.INTER_LINEAR):
    list_files = glob(path.join(folder_path, '*'))
    return images_from_list_files(list_files, output_size, output_type, bgr2rgb, interpolation), list_files

    
def images_from_list_files(list_files, output_size=None, output_type=np.float32, bgr2rgb=False, interpolation=cv2.INTER_LINEAR):
    assert(output_size is None or len(output_size) == 2)

    n_files = len(list_files)

    im = cv2.imread(list_files[0], cv2.IMREAD_ANYCOLOR)
    is_gray = len(im.shape) == 2
    output_size = (im.shape[0], im.shape[1]) if output_size is None else output_size
    image_tensor = np.empty(shape=(n_files, output_size[1], output_size[0], 1 if is_gray else im.shape[2]), dtype=output_type)

    for i, file in enumerate(list_files):
        print('{} of {}'.format(i+1, n_files), end='\r')
        stdout.flush()

        im = cv2.imread(file, cv2.IMREAD_ANYCOLOR)

        if (not is_gray) and bgr2rgb:
            im = cv2.cvtColor(im, cv2.COLOR_BGR2RGB)

        im = cv2.resize(im, output_size, interpolation=interpolation).astype(output_type)
        image_tensor[i] = np.expand_dims(im, axis=2) if is_gray else im
    print()

    return image_tensor


def mrk_files_from_folder(folder_path):
    mrk_filepaths = glob(path.join(folder_path, '*.mrk'))
    return mrk_files_from_list_files(mrk_filepaths)


def mrk_files_from_list_files(list_files):
    mrk_files = []
    for i, mrk_path in enumerate(list_files):
        print('{} of {}'.format(i+1, len(list_files)), end='\r')
        stdout.flush()

        mrk_files.append(MRKFile.from_file(mrk_path))
    print()
    return np.array(mrk_files)