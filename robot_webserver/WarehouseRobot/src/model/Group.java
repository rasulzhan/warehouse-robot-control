package model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import java.util.ArrayList;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 01.04.13
 * Time: 10:49
 * To change this template use File | Settings | File Templates.
 */
@Entity(name = "Group")
public class Group {

    @Id
    private Long id;

    @Column(name="label")
    private String label;

    @Column(name="weight")
    private double weight;

    public Group() {
    }

    public Group(Long id) {
        this.id = id;
    }

    public Group(Long id, String label, double weight) {
        this.id = id;
        this.label = label;
        this.weight = weight;
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
}
