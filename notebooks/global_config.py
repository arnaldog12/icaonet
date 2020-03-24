# training params
USER_IDS = "1_3_5"
IMAGE_SIZE = (224, 224)
RANDOM_SEED = 42

# folders
FOLDER_IMAGES = '../data/pybossa/images/'
FOLDER_MRKS = f'../data/pybossa/ground_truth/{USER_IDS}/'
FOLDER_MODELS = '../models/autoencoders_requirements/'

# files
FILE_DUMP_IMAGES = '../data/pybossa/pybossa_images.pkl'
FILE_DUMP_MRKS = '../data/pybossa/pybossa_mrks.pkl'
