from data_structures import Eye
from iso_standard import PhotographicRequirements

class MRKFile():
    """A class to load and save MRK files."""

    def __init__(self, right_eye, left_eye, photo_reqs, filepath=None):
        self.right_eye = right_eye
        self.left_eye = left_eye
        self.photo_reqs = photo_reqs
        self.filepath = filepath

    @classmethod
    def from_file(cls, filepath):
        right_eye, left_eye, photo_reqs = MRKFile.__load(filepath)
        return cls(right_eye, left_eye, photo_reqs, filepath)

    @staticmethod
    def __load(filepath):
        with open(filepath, 'r') as mrk_file:
            right_eye = Eye(*map(int, mrk_file.readline().replace('\n', '').split(' ')))
            left_eye = Eye(*map(int, mrk_file.readline().replace('\n', '').split(' ')))
            photo_reqs = PhotographicRequirements(*[int(line.replace('\n', '')) for line in mrk_file.readlines()])
        return (right_eye, left_eye, photo_reqs)

    def save(self, filepath):
        with open(filepath, 'w') as mrk_file:
            mrk_file.write('{} {} {} {}\n'.format(self.right_eye.left_corner.x, self.right_eye.left_corner.y, self.right_eye.right_corner.x, self.right_eye.right_corner.y))
            mrk_file.write('{} {} {} {}\n'.format(self.left_eye.left_corner.x, self.left_eye.left_corner.y, self.left_eye.right_corner.x, self.left_eye.right_corner.y))

            for req in self.photo_reqs:
                mrk_file.write('{}\n'.format(req.value))

    def __str__(self):
        output_str = 'Right Eye => {}\n'.format(self.right_eye.__str__())
        output_str += ' Left Eye => {}\n'.format(self.left_eye.__str__())
        output_str += self.photo_reqs.__str__()
        return output_str
