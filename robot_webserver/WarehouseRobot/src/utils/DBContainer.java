package utils;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.*;
import java.util.Properties;

/**
 * Created by IntelliJ IDEA.
 * User: Rasulzhan
 * Date: 01.04.13
 * Time: 11:04
 * To change this template use File | Settings | File Templates.
 */
public class DBContainer {

    private String url = "jdbc:postgresql://localhost:5432/warehouse";//"jdbc:postgresql://postgres-warehouse.j.rsnx.ru/warehouse";
    private String username="postgres";
    private String password="postgres";
    private Connection connection;
    public DBContainer() throws SQLException, ClassNotFoundException {
        Class.forName("org.postgresql.Driver");
        connection = null;
        connection = DriverManager.getConnection(url, username, password);
    }
//
//    public DBContainer() throws IOException, ClassNotFoundException, SQLException {
////        Connection connection;
//
//        Properties prop = new Properties();
//        System.out.println("test");
//        prop.load(new FileInputStream(System.getProperty("user.home") + "/mydb.cfg"));
//        System.out.println("user.home: "+System.getProperty("user.home"));
//        String host = prop.getProperty("host").toString();
//        String username = prop.getProperty("username").toString();
//        String password = prop.getProperty("password").toString();
//        String driver = prop.getProperty("driver").toString();
//
//
//        Class.forName(driver);
//        System.out.println("--------------------------");
//        System.out.println("DRIVER: " + driver);
//        connection = DriverManager.getConnection(host, username, password);
//        System.out.println("CONNECTION: " + connection);
//    }

    public PreparedStatement getStatement(String query) throws SQLException {
        return connection.prepareStatement(query);
    }
    
    public ResultSet select(String query) throws SQLException {
        PreparedStatement stmt = connection.prepareStatement(query);
        return stmt.executeQuery();
    }

    public void close() throws SQLException {
        connection.close();
    }

}
