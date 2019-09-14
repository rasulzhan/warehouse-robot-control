package servlets;

import utils.DBContainer;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 05.04.13
 * Time: 6:44
 * To change this template use File | Settings | File Templates.
 */
public class PathRequest extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            response.setCharacterEncoding("UTF-8");
            response.setContentType("text/html; charset=UTF-8");

            request.setCharacterEncoding("UTF-8");

            DBContainer db = new DBContainer();
            ResultSet rs = db.select("SELECT * from robot_paths order by path_id");
            if(rs == null || rs.next()==false) return;
            PrintWriter out = response.getWriter();
            String path = rs.getString("path");

            long path_id = rs.getLong("path_id");


            PreparedStatement stmt = db.getStatement("DELETE FROM robot_paths where path_id=?");
            stmt.setLong(1,path_id);
            stmt.execute();
            db.close();
            out.print(path);
            out.flush();
            out.close();
        } catch (SQLException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        } catch (ClassNotFoundException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
