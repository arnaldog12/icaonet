using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;

namespace MrkReview
{
    public class MRKFile
    {
        public string FilePath { get; set; }
        public Eye RightEye { get; set;  }
        public Eye LeftEye { get; set; }
        public PhotographicRequirements PhotoReqs { get; set; }

        public MRKFile(string filePath)
        {
            this.FilePath = filePath;
            this.Load();
        }

        public void Save()
        {
            List<string> lines = new List<string>();
            lines.Add($"{this.RightEye.RightCorner.X} {this.RightEye.RightCorner.Y} {this.RightEye.LeftCorner.X} {this.RightEye.LeftCorner.Y}");
            lines.Add($"{this.LeftEye.RightCorner.X} {this.LeftEye.RightCorner.Y} {this.LeftEye.LeftCorner.X} {this.LeftEye.LeftCorner.Y}");
            
            foreach (Requirement req in this.PhotoReqs)
                lines.Add($"{(int) req.Value}");

            System.IO.File.WriteAllLines(this.FilePath, lines);
        }

        private void Load()
        {
            string[] fileLines = File.ReadAllLines(this.FilePath);

            string[] eyePoints;
            Point rightCorner, leftCorner;

            eyePoints = fileLines[0].Split(' ');
            rightCorner = new Point(Int32.Parse(eyePoints[0]), Int32.Parse(eyePoints[1]));
            leftCorner = new Point(Int32.Parse(eyePoints[2]), Int32.Parse(eyePoints[3]));
            this.RightEye = new Eye(rightCorner, leftCorner);

            eyePoints = fileLines[1].Split(' ');
            rightCorner = new Point(Int32.Parse(eyePoints[0]), Int32.Parse(eyePoints[1]));
            leftCorner = new Point(Int32.Parse(eyePoints[2]), Int32.Parse(eyePoints[3]));
            this.LeftEye = new Eye(rightCorner, leftCorner);

            this.PhotoReqs = new PhotographicRequirements(
                blurred: (REQUIREMENT_VALUE)Int32.Parse(fileLines[2]),
                lookingAway: (REQUIREMENT_VALUE)Int32.Parse(fileLines[3]),
                inkMarkedCreased: (REQUIREMENT_VALUE)Int32.Parse(fileLines[4]),
                unnaturalSkinTone: (REQUIREMENT_VALUE)Int32.Parse(fileLines[5]),
                tooDarkLight: (REQUIREMENT_VALUE)Int32.Parse(fileLines[6]),
                washedOut: (REQUIREMENT_VALUE)Int32.Parse(fileLines[7]),
                pixelation: (REQUIREMENT_VALUE)Int32.Parse(fileLines[8]),
                hairAcrossEyes: (REQUIREMENT_VALUE)Int32.Parse(fileLines[9]),
                eyesClosed: (REQUIREMENT_VALUE)Int32.Parse(fileLines[10]),
                variedBackground: (REQUIREMENT_VALUE)Int32.Parse(fileLines[11]),
                rollPitchYaw: (REQUIREMENT_VALUE)Int32.Parse(fileLines[12]),
                flashReflectionOnSkin: (REQUIREMENT_VALUE)Int32.Parse(fileLines[13]),
                redEyes: (REQUIREMENT_VALUE)Int32.Parse(fileLines[14]),
                shadowsBehindHead: (REQUIREMENT_VALUE)Int32.Parse(fileLines[15]),
                shadowsAcrossFace: (REQUIREMENT_VALUE)Int32.Parse(fileLines[16]),
                darkTintedLenses: (REQUIREMENT_VALUE)Int32.Parse(fileLines[17]),
                flashReflectionOnLenses: (REQUIREMENT_VALUE)Int32.Parse(fileLines[18]),
                framesTooHeavy: (REQUIREMENT_VALUE)Int32.Parse(fileLines[19]),
                frameCoveringEyes: (REQUIREMENT_VALUE)Int32.Parse(fileLines[20]),
                hatCap: (REQUIREMENT_VALUE)Int32.Parse(fileLines[21]),
                veilOverFace: (REQUIREMENT_VALUE)Int32.Parse(fileLines[22]),
                mouthOpen: (REQUIREMENT_VALUE)Int32.Parse(fileLines[23]),
                presenceOfOtherFacesOrToys: (REQUIREMENT_VALUE)Int32.Parse(fileLines[24]));
        }
    }
}
