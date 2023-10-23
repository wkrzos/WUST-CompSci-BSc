package old;


class Page {
    private int id;
    private int arriveTime;
    private int lastUsed;

    public Page(int id) {
        this.id = id;
        this.arriveTime = 0;
        this.lastUsed = 0;
    }

    public int getId() {
        return id;
    }

    public int getArriveTime() {
        return arriveTime;
    }

    public void setArriveTime(int arriveTime) {
        this.arriveTime = arriveTime;
    }

    public int getLastUsed() {
        return lastUsed;
    }

    public void setLastUsed(int lastUsed) {
        this.lastUsed = lastUsed;
    }
}