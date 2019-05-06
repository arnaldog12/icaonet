using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MrkReview
{
    public class GTPair
    {
        public string FileImage { get; set; }
        public MRKFile FileMrk { get; set; }

        public GTPair(string fileImage, MRKFile fileMRK)
        {
            this.FileImage = fileImage;
            this.FileMrk = fileMRK;
        }
    }
}
