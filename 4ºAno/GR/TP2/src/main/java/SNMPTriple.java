public  class SNMPTriple
{
    public String oid;
    public String name;
    public String value;

    public SNMPTriple(String oid, String name, String value)
    {
        this.oid = oid;
        this.name = name;
        this.value = value;
    }




    public String getValue() {
        return value;
    }


}