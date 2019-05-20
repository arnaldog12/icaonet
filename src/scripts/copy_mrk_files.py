from glob import glob
from os.path import splitext, split
from shutil import copyfile

folder_gt = 'E:/Documents/Arnaldo/GitHub/doutorado/data/val/FVC/images/'
folder_mrk = 'E:/Downloads/fvc/Data/Trainingset/Mrk/'

list_images = glob(folder_gt + '*')
print(len(list_images))

for file_img in list_images:
	_, file_img = split(file_img)
	file_mrk = folder_mrk + splitext(file_img)[0] + '.mrk'
	copyfile(file_mrk, 'output/' + split(file_mrk)[1])
