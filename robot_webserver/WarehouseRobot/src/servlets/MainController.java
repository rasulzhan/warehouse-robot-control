package servlets;

import com.google.gson.Gson;
import utils.Group;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Locale;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 01.04.13
 * Time: 9:49
 * To change this template use File | Settings | File Templates.
 */
public class MainController extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String id = request.getParameter("name");

        response.setCharacterEncoding("UTF-8");
        response.setContentType("text/html; charset=UTF-8");

        request.setCharacterEncoding("UTF-8");

        PrintWriter out = response.getWriter();

        if(id == null)id = "-1";

        FileInputStream fis = new FileInputStream(
                request.getRealPath("/").toString()
                        +"/data.json");
        BufferedReader in = new BufferedReader(
                new InputStreamReader(fis,"UTF-8"));
        if(in != null) {
            char[] buff = new char[1];
            int line;
            ByteArrayOutputStream by = new ByteArrayOutputStream();
            String result = "";
            while((line = in.read(buff,0,1))>=0) {
                String str = new String(buff);

                result+=str;
            }


            Group group  = new Gson().fromJson(result,Group.class);
            String r = takeInfo(group,id);
            out.println(r);
            System.out.println(group);
        }
        out.flush();
        out.close();
    }

    public String takeInfo(Group group, String id) {
        if(id == null)return "<h1>Incorrect ID!</h1>";
        Long idl = Long.parseLong(id);
        if(group != null) {
            if(group.getId()!= null && (group.getId().equals(idl))) {
                if(group.getGroups() != null) {
                    if(group.getGroups().size()>0) {
                        String res = "";
                        for(Group gr:group.getGroups()) {
                            res+="<div class=\"group\">"+oneGroup(gr)+"</div>";
                        }
                        return res;
                    } else
                        return oneGroup(group);
                } else {
                    return oneGroup(group);
                }
            } else {
                String res = "";
                for(Group gr:group.getGroups()) {
                   res += takeInfo(gr,id);
                }
                return res;
            }
        } else return "";
    }
    
    public String oneGroup(Group group) {
        String res =  "<h1>"+group.getLabel()+"</h1>";
        res += "<h2>Количество: "+group.getWeight()+"</h2>";
        res += "<form action=\"Order" +
                "\"><input type='hidden' name='path' value='"+
                group.getPath()+"'><" +
                "input type='submit' value='Заказать'/></form>";
        return res;
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
