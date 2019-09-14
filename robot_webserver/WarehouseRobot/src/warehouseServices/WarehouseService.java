package warehouseServices;

import model.MyGroup;
import utils.DBContainer;

import java.io.*;
import java.math.BigDecimal;
import java.net.URL;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 01.04.13
 * Time: 9:42
 * To change this template use File | Settings | File Templates.
 */
public class WarehouseService {

    DBContainer dbContainer;
    ArrayList<MyGroup> groups;
    HashMap<Long,MyGroup>  groupMap;
    HashMap<Long,ArrayList<MyGroup>>  subGroupMap;
    HashMap<Long,HashSet<Long>> tree;
    HashSet<Long> roots;
    
    Queue<String> paths;
    

    public WarehouseService() {
        paths = new LinkedList<String> ();
//        try {
////            dbContainer = new DBContainer();
////            tree = new HashMap<Long, HashSet<Long>>();
////            groupMap = new HashMap<Long, MyGroup>();
////            roots = new HashSet<Long>();
//
//        } catch (SQLException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        } catch (ClassNotFoundException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        }
    }

    public String sayHelloWorldFrom(String from) {
        String result = "Hello, world, from " + from;
        System.out.println(result);
        return result;
    }

    public void orderPath(String path) {
        paths.add(path);
    }

    public String takePath() {
        if(paths==null || (paths.size()==0))return null;
        return paths.remove();
    }

//    public String getGroup(String id) {
//        return null;
//    }
//
//    public String takeValues(String name) {
//        String out = "";
//         out += "<div>Hello My Friend, "+name+"!</div>";
//        out += "<br />";
//        if(name == null)name = "Incognito";
//
//        ClassLoader cl = this.getClass().getClassLoader();
//        URL url = cl.getResource("data-mining-100-topic-hierarchical.jsonp");
//        FileInputStream fis = null;
//        try {
//            fis = new FileInputStream(url.getPath());
//        BufferedReader in = null;
//
//            in = new BufferedReader(
//                    new InputStreamReader(fis,"UTF-8"));
//
//        if(in != null) {
//            char[] buff = new char[1];
//            int line;
//            ByteArrayOutputStream by = new ByteArrayOutputStream();
//            String result = "";
//            while((line = in.read(buff,0,1))>=0) {
//                String str = new String(buff);
//                result+=str;
//            }
//
//            out += result;
//            System.out.println(result);
//
//        }
//
//
//
//            return out;
//
//        } catch (UnsupportedEncodingException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        } catch (FileNotFoundException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        } catch (IOException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        }
//        return "";
//    }
//
//    public String takeCarrotModel() {
//        try {
//            ResultSet result = dbContainer.select("select * from mygroup order by parentid");
//            if(result == null) return "";
//
//            while(result.next()) {
//                Long id = result.getLong("id");
//                Long parentid = result.getLong("parentid");
//                String label = result.getString("label");
//                double weight = result.getDouble("weight");
//                if(parentid != null) {
//                    if(!tree.containsKey(parentid)) {
//                        tree.put(parentid,new HashSet<Long>());
//                    }
//                    tree.get(parentid).add(id);
//                }else {
//                    roots.add(id);
//                }
//                MyGroup group = new MyGroup(id,label,weight,null,null,parentid);
//                groupMap.put(id,group);
//            }
//
//
//
//            String str = "{";
//            int i = 0;
//            while(result.next()) {
//                BigDecimal id = result.getBigDecimal("id");
//                BigDecimal parentid = result.getBigDecimal("parentid");
//                String label = result.getString("label");
//                double weight = result.getDouble("weight");
//                if(i != 0)
//                    str += ",";
//                else i++;
//                str += "{";
//
//                str += "id:"+id.longValue();
//                str += ",";
//
//                str += "parentid:"+((parentid == null)?"":parentid.longValue());
//                str += ",";
//
//                str += "label:"+"'"+label+"'";
//                str += ",";
//
//                str += "weight:"+weight;
//
//                str +=  "}";
//            }
//            str+="}";
//            return str;
//        } catch (SQLException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        }
//        return null;
//    }
//
//    public String checkDB() {
//        try {
//            ResultSet result = dbContainer.select("select * from mygroup where parentid is not null");
//            if(result == null) return "";
//            String str = "{";
//            int i = 0;
//            while(result.next()) {
//                BigDecimal id = result.getBigDecimal("id");
//                BigDecimal parentid = result.getBigDecimal("parentid");
//                String label = result.getString("label");
//                double weight = result.getDouble("weight");
//                if(i != 0)
//                    str += ",";
//                else i++;
//                str += "{";
//
//                str += "id:"+id.longValue();
//                str += ",";
//
//                str += "parentid:"+((parentid == null)?"":parentid.longValue());
//                str += ",";
//
//                str += "label:"+"'"+label+"'";
//                str += ",";
//
//                str += "weight:"+weight;
//
//                str +=  "}";
//            }
//            str+="}";
//            return str;
//        } catch (SQLException e) {
//            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
//        }
//        return null;
//    }

}
