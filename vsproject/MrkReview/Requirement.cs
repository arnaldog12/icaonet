namespace MrkReview
{
    public enum REQUIREMENT_VALUE
    {
        COMPLIANT = 1,
        NON_COMPLIANT = 0,
        DUMMY = -1
    }

    public class Requirement
    {
        public int Id { get; }
        public string Description { get; }
        public REQUIREMENT_VALUE Value { get; set; }

        public Requirement(int id, string description, REQUIREMENT_VALUE value)
        {
            this.Id = id;
            this.Description = description;
            this.Value = value;
        }
    }
}
