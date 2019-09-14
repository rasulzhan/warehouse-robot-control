package utils;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 05.04.13
 * Time: 4:54
 * To change this template use File | Settings | File Templates.
 */

import java.util.ArrayList;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 01.04.13
 * Time: 10:49
 * To change this template use File | Settings | File Templates.
 */
public class Group {

    private Long id;
    private String label;
    private double weight;
    private String path;
    private ArrayList<Group> groups;

    public Group() {
        groups = new ArrayList<Group>();
    }

    public Group(Long id, String label, double weight, String path, ArrayList<Group> groups) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        this.path = path;
        this.groups = groups;
    }

    public Group(Long id, String label, double weight, String path) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        this.path = path;
    }

    public Group(Long id) {
        this.id = id;
        groups = new ArrayList<Group>();
    }

    public Group(Long id, String label, double weight) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        groups = new ArrayList<Group>();
    }

    public Group(Long id, String label, double weight, ArrayList<Group> groups) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        this.groups = groups;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public ArrayList<Group> getGroups() {
        return groups;
    }

    public void setGroups(ArrayList<Group> groups) {
        this.groups = groups;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String toString() {
        String result = "\n{label:\""+label+"\",weight:"+weight+",id:"+id+",path:\""+path+"\",groups:[";
        int i = 0;
        for(Group g:groups) {
            if(i != 0) {
                result+=",";
            } else i++;
            result+=("\t"+g);
        }
        result+="\n]}";
        return result;
    }
}
