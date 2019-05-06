using System.Drawing;

namespace MrkReview
{
    public class Eye
    {
        public Point RightCorner { get; }
        public Point LeftCorner { get; }

        public Eye(Point rightCorner, Point leftCorner)
        {
            this.RightCorner = rightCorner;
            this.LeftCorner = leftCorner;
        }
    }
}
