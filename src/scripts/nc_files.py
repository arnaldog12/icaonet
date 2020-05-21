from sys import path
path.append('..')

import numpy as np
from os.path import basename, splitext
from glob import glob
from utils import load
from mrk_file import MRKFile

list_files = np.array(glob("../../data/val/FVC/images/*"))
list_files = np.array([file for file in list_files if splitext(file)[1].lower() in ['.png', '.jpg']])

list_mrks = [splitext(file)[0] + '.mrk' for file in list_files]
list_mrks = [file.replace('images', 'ground_truth') for file in list_mrks]

mrk_files = load.mrk_files_from_list_files(list_mrks)

nc_mask = [mrk.photo_reqs.too_dark_light.is_non_compliant() for mrk in mrk_files]
nc_files = list_files[nc_mask]
nc_files = [basename(file) for file in nc_files]

OUTPUT_FILE = 'C:/Users/arnal/Documents/GitHub/doutorado/data/siamese_networks/too_dark_light/negatives.txt'
with open(OUTPUT_FILE, 'w') as output_file:
    output_file.writelines('\n'.join(nc_files))