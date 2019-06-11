using System.Drawing;

namespace MrkReview
{
    public class Eye
    {
        public Point LeftCorner { get; }
        public Point RightCorner { get; }

        public Eye(Point leftCorner, Point rightCorner)
        {
            this.LeftCorner = leftCorner;
            this.RightCorner = rightCorner;
        }
    }
}
