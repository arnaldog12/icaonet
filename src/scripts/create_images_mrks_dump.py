import sys
sys.path.append('../')

import cv2
import numpy as np
import pickle as pkl
from os.path import basename, splitext
from mrk_file import MRKFile
from glob import glob


FOLDER_IMAGES = '../../data/pybossa/images/'
FOLDER_MRKS = '../../data/pybossa/ground_truth/1/'
OUTPUT_FILE = '../../data/pybossa/pybossa.pkl'
OUTPUT_SIZE = (224, 224)

list_images = glob(FOLDER_IMAGES + '*')
n_images = len(list_images)

x = np.zeros((n_images, *OUTPUT_SIZE, 3))
list_mrks = []
for i, image_path in enumerate(list_images):
    print(f'{i + 1} of {n_images}', end='\r')

    im = cv2.imread(image_path, cv2.IMREAD_COLOR)
    im = cv2.resize(im, OUTPUT_SIZE, interpolation=cv2.INTER_AREA)
    x[i] = im

    image_name, _ = splitext(basename(image_path))
    mrk_file = f'{FOLDER_MRKS}{image_name}.mrk'
    mrk = MRKFile.from_file(mrk_file)
    list_mrks.append(mrk)

pkl.dump((x, list_mrks), open(OUTPUT_FILE, 'wb'), protocol=-1)
