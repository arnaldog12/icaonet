from os.path import join
from shutil import copy2

def copy_files(list_files, input_folder, output_folder):
    for file in list_files:
        file = file.replace('\n', '')

        input_file = join(input_folder, file)
        try:
            copy2(input_file, output_folder)
        except:
            print(input_file)
            pass


ROOT_FOLDER = "C:/Users/arnal/Documents/GitHub/doutorado/data/siamese_networks/presence_of_other_faces_or_toys"
IMAGE_FOLDER = "C:/Users/arnal/Documents/GitHub/doutorado/data/cropped_faces/images/"

file_positives = open(f"{ROOT_FOLDER}/positives.txt", "r").readlines()
file_negatives = open(f"{ROOT_FOLDER}/negatives.txt", "r").readlines()

intersection = set(file_positives).intersection(file_negatives)
assert(len(intersection) == 0), intersection

copy_files(file_positives, IMAGE_FOLDER, f"{ROOT_FOLDER}/positives/")
copy_files(file_negatives, IMAGE_FOLDER, f"{ROOT_FOLDER}/negatives/")

