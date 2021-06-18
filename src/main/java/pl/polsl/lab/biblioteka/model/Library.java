/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.biblioteka.model;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Library model, contains an ArrayList of books and a Map of users.
 * 
 * @author Witold
 * @version 1.2
 */
public class Library {
    /**
     * List of books in the library.
     */
    private ArrayList<Book> booksList;
    /**
     * Map of users registered in the library with their passwords. 
     */
    private Map<String, String> users;
    /**
     * Name of the currently logged user.
     */
    String loggedUser;

    public Library() {
        booksList = new ArrayList<Book>();
        users = new HashMap<>();
    }

    public Library(ArrayList<Book> booksList) {
        this.booksList = booksList;
    }
    /**
     * Book list getter.
     * @return The entire ArrayList of book objects.
     */
    public ArrayList<Book> getBooksList() {
        return booksList;
    }
    
    public void setBooksList(ArrayList<Book> booksList) {
        this.booksList = booksList;
    }
    
    /**
     * Book getter function.
     * @param id Index of the book in the book ArrayList..
     * @return The book object.
     */
    public Book getBookById(int id) {
        return this.booksList.get(id);
    }
    
    public String getLoggedUser(){
        return this.loggedUser;
    }
    
    public void setLoggedUser(String user){
        this.loggedUser = user;
    }
    
    /**
     * Custom exception for handling omission of any text
     * field while adding new book by hand.
     */
    public class AddBookIncompleteDataException extends RuntimeException {
        public AddBookIncompleteDataException(String errorMessage){
            super(errorMessage);
        }
    }
    
    /**
     * Custom exception for handling invalid year input.
     */
    public class InvalidYearException extends RuntimeException {
        public InvalidYearException(String errorMessage){
            super(errorMessage);
        }
    }
    
    /**
     * Adds a book object to the book ArrayList
     * @param book A book to be added to the ArrayList.
     */
    public void AddBook(Book book){
        if(book.checkBookInfo()){
            throw new AddBookIncompleteDataException("Incomplete book data.");
        }
        else if(book.verifyYear()){
            throw new InvalidYearException("Invalid year.");
        }
        else{
            this.booksList.add(book);
        }
    }
    
    /**
     * Removes a book from the book ArrayList.
     * @param id Index of the book to be removed from the book ArrayList.
     */
    public void RemoveBook(int id){
        this.booksList.remove(id);
    }
    
    /**
     * List length getter.
     * @return Number of books in the book ArrayList.
     */
    public int GetListLength(){
        return this.booksList.size();
    }
    
    /**
     * Auxiliary function for debugging, prints the most vital
     * fields of all book objects from the book ArrayList.
     */
    public void PrintList(){
        for(Book x: booksList){
            System.out.println(x.getName() + " " + x.getAuthor() + " " + x.getPublisher() + " " + x.getGen() +" " + Integer.toString(x.getYear())+ " ID: " + Integer.toString(x.getId()) + " " + x.getIsAvailable());
        }
    }
    
    /**
     * Function for adjusting books' identification numbers.
     * Used after removal, allows for consistent numbering
     * of the books.
     */
    public void UpdateIDs(){
        int i = 1;
        for(Book x: booksList){
            x.setId(i);
            i++;
        }
    }
    
    /**
     * Custom exception for handling omission of either
     * the username or the password while signing in.
     */
    public class LogInInputException extends RuntimeException {
        public LogInInputException(String errorMessage){
            super(errorMessage);
        }
    }
    
    /**
     * Function for verification of username and password
     * given for signing in.
     * @param name Given username.
     * @param password Given password.
     * @return Returns true if valid information has been given.
     */
    public boolean verifyUser(String name, String password){
        if(name.isEmpty()){
            throw new LogInInputException("Username is required!");
        }
        else if(password.isEmpty()){
            throw new LogInInputException("Password is required!");
        }
        else if(users.containsKey(name)){
            if(password.equals(users.get(name))){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    
    /**
     * Adds a user to the users map.
     * @param name Given username.
     * @param password Given password.
     */
    public void addUser(String name, String password){
        users.put(name, password);
    }
    
    /**
     * Function for veryfing whether the given username is occupied.
     * @param name Given username.
     * @return Returns true if the username is already taken.
     */
    public boolean isUsernameTaken(String name){
        return users.containsKey(name);
    }
    
    /**
     * Function for loading books list from a text file.
     * @param filename Name of the input file.
     */
    public void LoadBooksFromFile(String filename){
        File file = new File(filename);
        try{
            Scanner input = new Scanner(file);
            String buffer;
            String[] bookFields;
            while(input.hasNextLine()){
                buffer = input.nextLine();
                bookFields = buffer.split(",");
                if("true".equals(bookFields[5])){
                    try{
                        this.AddBook(new Book(bookFields[0], bookFields[1], bookFields[2], Integer.parseInt(bookFields[3]), 0, bookFields[4], true));
                    }
                    catch(AddBookIncompleteDataException | InvalidYearException e){
                        System.out.println(e.getMessage());
                    }
                }
                else{
                    try{
                        this.AddBook(new Book(bookFields[0], bookFields[1], bookFields[2], Integer.parseInt(bookFields[3]), 0, bookFields[4], false, bookFields[6], bookFields[7]));
                    }
                    catch(AddBookIncompleteDataException | InvalidYearException e){
                        System.out.println(e.getMessage());
                    }
                }
            }
            input.close();
            this.UpdateIDs();
        }
        catch(FileNotFoundException e){
            System.out.printf("ERROR: %s\n", e);
        }
    }
    
    /**
     * Function for saving books list in a text file.
     */
    public void WriteBooksToFile(){
        try{
            FileWriter writer = new FileWriter("books.txt");
            for(Book b : this.booksList)
            {
                if(b.getIsAvailable()){
                    writer.write(b.getName()+","+b.getAuthor()+","+b.getPublisher()+","+Integer.toString(b.getYear())+","+b.getGen()+","+String.valueOf(b.getIsAvailable())+"\n");
                }
                else{
                    writer.write(b.getName()+","+b.getAuthor()+","+b.getPublisher()+","+Integer.toString(b.getYear())+","+b.getGen()+","+String.valueOf(b.getIsAvailable())+","+b.getHolder()+","+b.getDueDate()+"\n");
                }
            }
            writer.close();
        }
        catch(IOException e){
            System.out.println("ERROR");
        }
    }
    
    /**
     * Function for loading users into a map from a text file
     * @param filename Name of the input file.
     */
    public void LoadUsersFromFile(String filename){
        File file = new File(filename);
        try{
            Scanner input = new Scanner(file);
            String buffer;
            String[] userFields;
            while(input.hasNextLine()){
                buffer = input.nextLine();
                userFields = buffer.split(",");
                users.put(userFields[0], userFields[1]);
            }
            input.close();
            this.UpdateIDs();
        }
        catch(FileNotFoundException e){
            System.out.printf("ERROR");
        }
    }
    
    /**
     * Function for saving users in a text file.
     */
    public void WriteUsersToFile(){
        try{
            FileWriter writer = new FileWriter("users.txt");
            users.forEach((k, v) -> {
                try {
                    writer.write(k+","+v+"\n");
                } catch (IOException ex) {
                    Logger.getLogger(Library.class.getName()).log(Level.SEVERE, null, ex);
                }
            });
            writer.close();
        }
        catch(IOException e){
            System.out.println("ERROR");
        }
    }
}
