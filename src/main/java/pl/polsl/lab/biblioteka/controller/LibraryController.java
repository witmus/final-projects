/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.biblioteka.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.stream.Stream;
import pl.polsl.lab.biblioteka.model.Book;
import pl.polsl.lab.biblioteka.model.Library;
import pl.polsl.lab.biblioteka.model.Library.LogInInputException;
import pl.polsl.lab.biblioteka.view.AddBookView;
import pl.polsl.lab.biblioteka.view.LibraryView;
import pl.polsl.lab.biblioteka.view.LogInRegisterView;

/**
 * Controller class, contains handlers for all
 * button listeners
 * 
 * @author Witold
 * @version 1.1
 */
public class LibraryController {
    /**
     * Main view of the library assigned to the controller.
     */
    private LibraryView libView;
    /**
     * Adding book view assigned to the controller.
     */
    private AddBookView addView;
    /**
     * Sign in and sign up view assigned to the controller.
     */
    private LogInRegisterView logInView;
    /**
     * Library model containing bokks list and users list.
     */
    private Library lib;

    public LibraryController() {
    }

    public LibraryController(LibraryView libview, AddBookView addview, Library library, LogInRegisterView loginview) {
        this.libView = libview;
        this.addView = addview;
        this.logInView = loginview;
        this.lib = library;
        
        this.libView.addAddingListener(new AddViewListener());
        this.libView.addLendReturnListener(new LendReturnListener());
        this.libView.addRemoveListener(new RemoveListener());
        this.addView.addButtonListener(new AddBookListener());
        this.logInView.addLoginListener(new LoginListener());
        this.logInView.addSignUpListener(new SignUpListener());
    }
    /**
     * Listener for displaying data input window.
     */
    class AddViewListener implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            addView.setVisible(true);
        }
        
    }
    /**
     * Listener for lending and returning selected books.
     */
    class LendReturnListener implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            int[] rows = libView.getRowsSelection();
            for(int i: rows){
                lib.getBookById(i).setIsAvailable(!(lib.getBookById(i).getIsAvailable()));
                if(lib.getBookById(i).getIsAvailable()){
                    if(lib.getBookById(i).getHolder().equals(lib.getLoggedUser())){
                        lib.getBookById(i).setDueDate(null);
                        lib.getBookById(i).setHolder(null);
                    }
                    else{
                        lib.getBookById(i).setIsAvailable(false);
                    }
                }
                else
                {
                    GregorianCalendar now = new GregorianCalendar();
                    now.add((GregorianCalendar.MONTH), 1);
                    SimpleDateFormat ft = new SimpleDateFormat("dd-MMM-yyyy");
                    Date deadline = now.getTime();
                    
                    String dueDate = ft.format(deadline);
                    
                    lib.getBookById(i).setDueDate(dueDate);
                    lib.getBookById(i).setHolder(lib.getLoggedUser());
                }
            }
            libView.clearTable();
            for(Book x: lib.getBooksList()){
                libView.addBookToTable(x);
            }
            lib.WriteBooksToFile();
        }
        
    }
    /**
     * Listener for removing selected books.
     */
    class RemoveListener implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            ArrayList<Book> newList = new ArrayList<>();
            int[] rows = libView.getRowsSelection();
            if(rows.length == 1){
                try{
                    lib.RemoveBook(rows[0]);
                }
                catch(IndexOutOfBoundsException ex){
                    System.out.println("Invalid book ID for removal");
                }
            }
            else{
                for(int i: rows){
                    if(lib.getBookById(i).getIsAvailable()){
                        lib.getBookById(i).setPublisher("");
                    }
                }
                Stream<Book> bookStream = lib.getBooksList().stream();
                Stream<Book> updatedStream = bookStream
                        .filter(b -> !(b.getPublisher().isBlank()));
                updatedStream.forEach((Book b) -> {newList.add(b);});
                lib.setBooksList(newList);
            }
            libView.clearTable();
            lib.UpdateIDs();
            for(Book x: lib.getBooksList()){
                libView.addBookToTable(x);
            }
            lib.WriteBooksToFile();
        }
        
    }
    /**
     * Listener for adding a book to the book list based
     * on data input from the user.
     */
    class AddBookListener implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            String title="";
            String author="";
            String publisher="";
            int year = 0;
            String genre = "";
            int id = 0;
        
            title = addView.getTitle();
            author = addView.getAuthor();
            publisher = addView.getPublisher();
            genre = addView.getGenre();
            id = lib.GetListLength() + 1;
        try{
            year = addView.getYear();
        }
        
        catch(NumberFormatException ex){
            
        }
            
            Book book = new Book(title, author, publisher, year, id, genre, true);
            try{
                lib.AddBook(book);
                lib.PrintList();
                addView.eraseFields();
                libView.addBookToTable(book);
                lib.WriteBooksToFile();
            }
            catch(Library.AddBookIncompleteDataException | Library.InvalidYearException exc){
                System.out.println(exc.getMessage());
            }
        }
        
    }
    /**
     * Listener for login button at the startup of the app.
     */
    class LoginListener implements ActionListener{
        
        @Override
        public void actionPerformed(ActionEvent e){
            
            try{
                    boolean login = lib.verifyUser(logInView.getUsername(), logInView.getPassword());
                    if(login){
                        lib.setLoggedUser(logInView.getUsername());
                        logInView.setVisible(false);
                        libView.setVisible(true);
                }
            }
            catch(LogInInputException ex){
                System.out.println(ex.getMessage());
            }
            
            
            logInView.ClearTextFields();
        }
    }
    
    /**
     * Listener for sign up button at the startup of the app.
     */
    class SignUpListener implements ActionListener{
        
        @Override
        public void actionPerformed(ActionEvent e){
            if(logInView.getUsername().isEmpty() || logInView.getPassword().isEmpty()){
                System.out.println("DEBUG SIGN UP");
            }
            else{
                if(!(lib.isUsernameTaken(logInView.getUsername()))){
                    lib.addUser(logInView.getUsername(), logInView.getPassword());
                }
            }
            lib.WriteUsersToFile();
            logInView.ClearTextFields();
        }
    }    
}
