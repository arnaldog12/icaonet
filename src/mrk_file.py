from data_structures import Eye
from iso_standard import PhotographicRequirements

class MRKFile():
    """A class to load and save MRK files."""

    def __init__(self, file_path):
        self.file_path = file_path
        self.right_eye = None
        self.left_eye = None
        self.photo_reqs = None
        self.__load()

    def __load(self):
        with open(self.file_path, 'r') as mrk_file:
            self.right_eye = Eye(*mrk_file.readline().replace('\n', '').split(' '))
            self.left_eye = Eye(*mrk_file.readline().replace('\n', '').split(' '))
            self.photo_reqs = PhotographicRequirements(*[int(line.replace('\n', '')) for line in mrk_file.readlines()])

    def save(self, file_path):
        with open(file_path, 'w') as mrk_file:
            mrk_file.write('{} {} {} {}\n'.format(self.right_eye.left_corner.x, self.right_eye.left_corner.y, self.right_eye.right_corner.x, self.right_eye.right_corner.y))
            mrk_file.write('{} {} {} {}\n'.format(self.left_eye.left_corner.x, self.left_eye.left_corner.y, self.left_eye.right_corner.x, self.left_eye.right_corner.y))

            for req in self.photo_reqs:
                mrk_file.write('{}\n'.format(req.value))

    def __str__(self):
        output_str = 'Right Eye => {}\n'.format(self.right_eye.__str__())
        output_str += ' Left Eye => {}\n'.format(self.left_eye.__str__())
        output_str += self.photo_reqs.__str__()
        return output_str
