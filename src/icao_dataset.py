import cv2
from os.path import join, basename, splitext
from utils import load
from sys import stdout


class ICAODataset():
    def __init__(self, folder_images, folder_mrks):
        self.folder_images = folder_images
        self.folder_mrks = folder_mrks
        self.image_files = []
        self.images = []
        self.mrks = []

    def load(self, **kwargs):
        self.images, self.image_files = load.images_from_folder(self.folder_images, **kwargs)

        mrk_file = lambda filepath: splitext(basename(filepath))[0] + ".mrk"
        list_mrks = [join(self.folder_mrks, mrk_file(file)) for file in self.image_files]
        self.mrks = load.mrk_files_from_list_files(list_mrks)

    def save(self, folder_images=None, folder_mrks=None, show_progress=True):
        folder_images = folder_images if folder_images else self.folder_images
        folder_mrks = folder_mrks if folder_mrks else self.folder_mrks

        n_files = len(self.image_files)
        i = 1
        for image_file, image, mrk in zip(self.image_files, self.images, self.mrks):
            if show_progress:
                print(f"{i} of {n_files}", end='\r')
                stdout.flush()
                i += 1

            output_img = join(folder_images, basename(image_file))
            output_mrk = join(folder_mrks, basename(mrk.filepath))
            cv2.imwrite(output_img, image)
            mrk.save(output_mrk)
