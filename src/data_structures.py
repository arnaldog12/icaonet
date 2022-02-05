class Point:
    """A class to represent a point."""

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return '({}, {})'.format(self.x, self.y)

    def __truediv__(self, other):
        return Point(self.x / other.x, self.y / other.y)


class Eye:
    """A class to represent an Eye according to ICAO standards."""

    def __init__(self, x_left, y_left, x_right, y_right):
        self.left_corner = Point(x_left, y_left)
        self.right_corner = Point(x_right, y_right)

    def __str__(self):
        return 'left corner: {} right_corner: {}'.format(self.left_corner, self.right_corner)
    
    def __truediv__(self, other):
        new_left = self.left_corner / other.left_corner
        new_right = self.right_corner / other.right_corner
        return Eye(new_left.x, new_left.y, new_right.x, new_right.y)


class Rect():
    def __init__(self, x, y, width=None, height=None):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def from_tl_br_points(tl, br):
        return Rect(tl[0], tl[1], br[0] - tl[0], br[1] - tl[1])

    def tl(self):
        '''return upper left point (x, y)'''
        return (self.x, self.y)

    def br(self):
        '''return bottom right point (x, y)'''
        return (self.x + self.width, self.y + self.height)

    def __str__(self):
        return '(x, y, width, height): ({}, {}, {}, {})'.format(self.x, self.y, self.width, self.height)

    def __add__(self, point):
        """Override sum operator. Same behavior as OpenCV."""
        return Rect(self.x + point.x, self.y + point.y, self.width, self.height)
