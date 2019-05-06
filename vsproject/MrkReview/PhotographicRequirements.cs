using System.Collections;
using System.Collections.Generic;

namespace MrkReview
{
    public class PhotographicRequirements : IEnumerable
    {
        public Requirement Blurred { get; }
        public Requirement LookingAway { get; }
        public Requirement InkMarkedCreased { get; }
        public Requirement UnnaturalSkinTone { get; }
        public Requirement TooDarkLight { get; }
        public Requirement WashedOut { get; }
        public Requirement Pixelation { get; }
        public Requirement HairAcrossEyes { get; }
        public Requirement EyesClosed { get; }
        public Requirement VariedBackground { get; }
        public Requirement RollPitchYaw { get; }
        public Requirement FlashReflectionOnSkin { get; }
        public Requirement RedEyes { get; }
        public Requirement ShadowsBehindHead { get; }
        public Requirement ShadowsAcrossFace { get; }
        public Requirement DarkTintedLenses { get; }
        public Requirement FlashReflectionOnLenses { get; }
        public Requirement FramesTooHeavy { get; }
        public Requirement FrameCoveringEyes { get; }
        public Requirement HatCap { get; }
        public Requirement VeilOverFace { get; }
        public Requirement MouthOpen { get; }
        public Requirement PresenceOfOtherFacesOrToys { get; }

        private List<Requirement> listReqs { get; }

        public PhotographicRequirements(REQUIREMENT_VALUE blurred = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE lookingAway = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE inkMarkedCreased = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE unnaturalSkinTone = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE tooDarkLight = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE washedOut = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE pixelation = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE hairAcrossEyes = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE eyesClosed = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE variedBackground = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE rollPitchYaw = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE flashReflectionOnSkin = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE redEyes = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE shadowsBehindHead = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE shadowsAcrossFace = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE darkTintedLenses = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE flashReflectionOnLenses = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE framesTooHeavy = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE frameCoveringEyes = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE hatCap = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE veilOverFace = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE mouthOpen = REQUIREMENT_VALUE.DUMMY,
                                        REQUIREMENT_VALUE presenceOfOtherFacesOrToys = REQUIREMENT_VALUE.DUMMY)
        {
            this.Blurred = new Requirement(1, "Blurred", blurred);
            this.LookingAway = new Requirement(2, "Looking away", lookingAway);
            this.InkMarkedCreased = new Requirement(3, "Ink marked/creased", inkMarkedCreased);
            this.UnnaturalSkinTone = new Requirement(4, "Unnatural skin tone", unnaturalSkinTone);
            this.TooDarkLight = new Requirement(5, "Too dark/light", tooDarkLight);
            this.WashedOut = new Requirement(6, "Washed out", washedOut);
            this.Pixelation = new Requirement(7, "Pixelation", pixelation);
            this.HairAcrossEyes = new Requirement(8, "Hair across eyes", hairAcrossEyes);
            this.EyesClosed = new Requirement(9, "Eyes closed", eyesClosed);
            this.VariedBackground = new Requirement(10, "Varied background", variedBackground);
            this.RollPitchYaw = new Requirement(11, "Roll/pitch/yaw rotations greater than a predefined thresholds", rollPitchYaw);
            this.FlashReflectionOnSkin = new Requirement(12, "Flash reflection on skin", flashReflectionOnSkin);
            this.RedEyes = new Requirement(13, "Red eyes", redEyes);
            this.ShadowsBehindHead = new Requirement(14, "Shadows behind head", shadowsBehindHead);
            this.ShadowsAcrossFace = new Requirement(15, "Shadows across face", shadowsAcrossFace);
            this.DarkTintedLenses = new Requirement(16, "Dark tinted lenses", darkTintedLenses);
            this.FlashReflectionOnLenses = new Requirement(17, "Flash reflection on lenses", flashReflectionOnLenses);
            this.FramesTooHeavy = new Requirement(18, "Frames too heavy", framesTooHeavy);
            this.FrameCoveringEyes = new Requirement(19, "Frame covering eyes", frameCoveringEyes);
            this.HatCap = new Requirement(20, "Hat/cap", hatCap);
            this.VeilOverFace = new Requirement(21, "Veil over face", veilOverFace);
            this.MouthOpen = new Requirement(22, "Mouth open", mouthOpen);
            this.PresenceOfOtherFacesOrToys = new Requirement(23, "Presence of other faces or toys too close to face", presenceOfOtherFacesOrToys);

            this.listReqs = new List<Requirement>(new Requirement[] { this.Blurred, this.LookingAway, this.InkMarkedCreased, this.UnnaturalSkinTone, this.TooDarkLight, this.WashedOut, this.Pixelation, this.HairAcrossEyes, this.EyesClosed, this.VariedBackground, this.RollPitchYaw, this.FlashReflectionOnSkin, this.RedEyes, this.ShadowsBehindHead, this.ShadowsAcrossFace, this.DarkTintedLenses, this.FlashReflectionOnLenses, this.FramesTooHeavy, this.FrameCoveringEyes, this.HatCap, this.VeilOverFace, this.MouthOpen, this.PresenceOfOtherFacesOrToys });
        }

        public IEnumerator GetEnumerator()
        {
            foreach(Requirement req in this.listReqs)
                yield return req;
        }

        public List<Requirement> GetRequirements()
        {
            return this.listReqs;
        }
    }
}
