class Point:
    """A class to represent a point."""

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return '({}, {})'.format(self.x, self.y)


class Eye:
    """A class to represent an Eye according to ICAO standards."""

    def __init__(self, x_left, y_left, x_right, y_right):
        self.left_corner = Point(x_left, y_left)
        self.right_corner = Point(x_right, y_right)

    def __str__(self):
        return 'left corner: {} right_corner: {}'.format(self.left_corner, self.right_corner)
