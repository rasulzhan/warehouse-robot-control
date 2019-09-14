package model;

import java.util.ArrayList;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 01.04.13
 * Time: 12:22
 * To change this template use File | Settings | File Templates.
 */
public class MyGroup {
    private long id;
    private String label;
    private double weight;
    private String forward;
    private String back;
    private long parentId;
    private ArrayList<MyGroup> groups;

    public MyGroup() {
        groups = new ArrayList<MyGroup>();
    }

    public MyGroup(long id) {
        this.id = id;
        groups = new ArrayList<MyGroup>();
    }

    public MyGroup(long id, String label) {
        this.id = id;
        this.label = label;
        groups = new ArrayList<MyGroup>();
    }

    public MyGroup(long id, String label, double weight) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        groups = new ArrayList<MyGroup>();
    }

    public MyGroup(long id, String label, double weight, String forward, String back) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        this.forward = forward;
        this.back = back;
        groups = new ArrayList<MyGroup>();
    }

    public MyGroup(long id, String label, double weight, String forward, String back, long parentId) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        this.forward = forward;
        this.back = back;
        this.parentId = parentId;
        groups = new ArrayList<MyGroup>();
    }

    public MyGroup(long id, String label, double weight, long parentId, ArrayList<MyGroup> groups, String forward, String back) {
        this.id = id;
        this.label = label;
        this.weight = weight;
        this.parentId = parentId;
        this.groups = groups;
        this.forward = forward;
        this.back = back;
        groups = new ArrayList<MyGroup>();
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
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

    public long getParentId() {
        return parentId;
    }

    public void setParentId(long parentId) {
        this.parentId = parentId;
    }

    public ArrayList<MyGroup> getGroups() {
        return groups;
    }

    public void setGroups(ArrayList<MyGroup> groups) {
        this.groups = groups;
    }

    public String getForward() {
        return forward;
    }

    public void setForward(String forward) {
        this.forward = forward;
    }

    public String getBack() {
        return back;
    }

    public void setBack(String back) {
        this.back = back;
    }
}
