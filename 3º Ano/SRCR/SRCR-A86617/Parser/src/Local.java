public class Local {
    private String id;
    private String city;
    private String lat;
    private String lng;
    private String capital;
    private String admin ;

    public Local(){
        id="";
        city="";
        lat="";
        lng="";
        capital="";
        admin="";
    }

    public Local (Local a){
        id=a.getId();
        city=a.getCity();
        lat=a.getLat();
        lng=a.getLng();
        capital=a.getCapital();
        admin=a.getAdmin();
    }

    public Local(String idA,String cityA,String latA, String lngA, String capitalA, String adminA){
        id=idA;
        city=cityA;
        lat=latA;
        lng=lngA;
        capital=capitalA;
        admin=adminA;

    }

    public String getId() {
        return id;
    }

    public String getCity() {
        return city;
    }

    public String getLat() {
        return lat;
    }

    public String getLng() {
        return lng;
    }

    public String getCapital() {
        return capital;
    }

    public String getAdmin() {
        return admin;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public void setLat(String lat) {
        this.lat = lat;
    }

    public void setLng(String lng) {
        this.lng = lng;
    }

    public void setCapital(String capital) {
        this.capital = capital;
    }

    public void setAdmin(String admin) {
        this.admin = admin;
    }

    public String toString() {
        String s;

        s = ("Local(" + this.id + "," + "'" +this.city + "'" + "," + this.lat+
                "," + this.lng + "," + "'" + this.capital +
                "'" + "," +"'" + this.admin +"'" + ").");
        return s;
    }
}
