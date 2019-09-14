package servlets;

import utils.DBContainer;
import warehouseServices.WarehouseService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 05.04.13
 * Time: 6:21
 * To change this template use File | Settings | File Templates.
 */
public class Order extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getParameter("path");
        if(path != null) {
            try {
                DBContainer db = new DBContainer();
                PreparedStatement stmt = db.getStatement("INSERT INTO robot_paths(path) values(?)");
                stmt.setString(1,path);
                stmt.execute();
                response.setCharacterEncoding("UTF-8");
                response.setContentType("text/html; charset=UTF-8");

                request.setCharacterEncoding("UTF-8");

                System.out.println(path);
                PrintWriter out = response.getWriter();
                out.println("<script>alert(\"Ваш Заказ успешно обработан!\");</script>");
                out.flush();
                db.close();
                request.getRequestDispatcher("/index.jsp").include(request,response);
            } catch (SQLException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            } catch (ClassNotFoundException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request,response);
    }
}
