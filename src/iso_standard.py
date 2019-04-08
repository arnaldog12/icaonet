class Requirement():
    """A class to represent a requirement."""

    def __init__(self, id, description, value=-1):
        self.id = id
        self.description = description
        self.value = value

    def __str__(self):
        return '[{:02}] {}: {}'.format(self.id, self.description, self.value)

    def is_compliant(self):
        """Check if the requirement is compliant (== 1)."""
        return self.value == 1

    def is_non_compliant(self):
        """Check if the requirement is non-compliant (== 0)."""
        return self.value == 0

    def is_dummy(self):
        """Check if the requirement is dummy (== -1)."""
        return self.value == -1


class PhotographicRequirements():
    """Photographic and pose-especific tests."""

    def __init__(self, blurred=-1, looking_away=-1, ink_marked_creased=-1, unnatural_skin_tone=-1, too_dark_light=-1, washed_out=-1, pixelation=-1, hair_across_eyes=-1, eyes_closed=-1, varied_background=-1, roll_pitch_yaw=-1, flash_reflection_on_skin=-1, red_eyes=-1, shadows_behind_head=-1, shadows_across_face=-1, dark_tinted_lenses=-1, flash_reflection_on_lenses=-1, frames_too_heavy=-1, frame_covering_eyes=-1, hat_cap=-1, veil_over_face=-1, mouth_open=-1, presence_of_other_faces_or_toys=-1):
        self.blurred = Requirement(2, 'Blurred', blurred)
        self.looking_away = Requirement(3, 'Looking away', looking_away)
        self.ink_marked_creased = Requirement(4, 'Ink marked/creased', ink_marked_creased)
        self.unnatural_skin_tone = Requirement(5, 'Unnatural skin tone', unnatural_skin_tone)
        self.too_dark_light = Requirement(6, 'Too dark/light', too_dark_light)
        self.washed_out = Requirement(7, 'Washed out', washed_out)
        self.pixelation = Requirement(8, 'Pixelation', pixelation)
        self.hair_across_eyes = Requirement(9, 'Hair across eyes', hair_across_eyes)
        self.eyes_closed = Requirement(10, 'Eyes closed', eyes_closed)
        self.varied_background = Requirement(11, 'Varied background', varied_background)
        self.roll_pitch_yaw = Requirement(12, 'Roll/pitch/yaw rotations greater than a predefined thresholds', roll_pitch_yaw)
        self.flash_reflection_on_skin = Requirement(13, 'Flash reflection on skin', flash_reflection_on_skin)
        self.red_eyes = Requirement(14, 'Red eyes', red_eyes)
        self.shadows_behind_head = Requirement(15, 'Shadows behind head', shadows_behind_head)
        self.shadows_across_face = Requirement(16, 'Shadows across face', shadows_across_face)
        self.dark_tinted_lenses = Requirement(17, 'Dark tinted lenses', dark_tinted_lenses)
        self.flash_reflection_on_lenses = Requirement(18, 'Flash reflection on lenses', flash_reflection_on_lenses)
        self.frames_too_heavy = Requirement(19, 'Frames too heavy', frames_too_heavy)
        self.frame_covering_eyes = Requirement(20, 'Frame covering eyes', frame_covering_eyes)
        self.hat_cap = Requirement(21, 'Hat/cap', hat_cap)
        self.veil_over_face = Requirement(22, 'Veil over face', veil_over_face)
        self.mouth_open = Requirement(23, 'Mouth open', mouth_open)
        self.presence_of_other_faces_or_toys = Requirement(24, 'Presence of other faces or toys too close to face', presence_of_other_faces_or_toys)
        self.__list_reqs = [self.blurred, self.looking_away, self.ink_marked_creased, self.unnatural_skin_tone, self.too_dark_light, self.washed_out, self.pixelation, self.hair_across_eyes, self.eyes_closed, self.varied_background, self.roll_pitch_yaw, self.flash_reflection_on_skin, self.red_eyes, self.shadows_behind_head, self.shadows_across_face, self.dark_tinted_lenses, self.flash_reflection_on_lenses, self.frames_too_heavy, self.frame_covering_eyes, self.hat_cap, self.veil_over_face, self.mouth_open, self.presence_of_other_faces_or_toys]

    def __iter__(self):
        for requirement in self.__list_reqs:
            yield requirement

    def __str__(self):
        return '\n'.join([req.__str__() for req in self.__list_reqs])

    def values(self):
        return [requirement.value for requirement in self.__list_reqs]
