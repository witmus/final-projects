/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.biblioteka.model;

import java.util.Calendar;
import java.util.GregorianCalendar;


/**
 * Book model class, contains fields describing a book and
 * complete set of getters and setters of all fields
 * 
 * @author Witold
 * @version 1.0
 */
public class Book {
    /**
     * Book's title.
     */
    private String name;
    /**
     * Book's author.
     */
    private String author;
    /**
     * Book's publisher.
     */
    private String publisher;
    /**
     * Due date of returning a book to the library.
     */
    private String dueDate;
    /**
     * Book's year of publishment.
     */
    private int year;
    /**
     * Book's identification number.
     */
    private int id;
    /**
     * Book's genre.
     */
    private String genre;
    /**
     * Book's state. Is true if the book is in the library,
     * and false, if it's been lent.
     */
    private boolean isAvailable;
    /**
     * Current book holder's username.
     */
    private String holder;  
    
    public Book() {
    }

    public Book(String name, String author, String publisher, int year, int id, String genre, boolean st) {
        this.name = name;
        this.author = author;
        this.publisher = publisher;
        this.year = year;
        this.id = id;
        this.genre = genre;
        this.isAvailable = st;
    }
    
    public Book(String name, String author, String publisher, int year, int id, String genre, boolean st, String user, String date) {
        this.name = name;
        this.author = author;
        this.publisher = publisher;
        this.year = year;
        this.id = id;
        this.genre = genre;
        this.isAvailable = st;
        this.dueDate = date;
        this.holder = user;
    }

    

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getPublisher() {
        return publisher;
    }

    public void setPublisher(String publisher) {
        this.publisher = publisher;
    }

    public String getDueDate() {
        return dueDate;
    }

    public void setDueDate(String dueDate) {
        this.dueDate = dueDate;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getGen() {
        return genre;
    }

    public void setGen(String gen) {
        this.genre = gen;
    }

    public boolean getIsAvailable() {
        return isAvailable;
    }

    public void setIsAvailable(boolean st) {
        this.isAvailable = st;
    }
    
    public String getHolder() {
        return holder;
    }

    public void setHolder(String holder) {
        this.holder = holder;
    }
    
    public boolean checkBookInfo(){
        if(this.author.isBlank()||this.name.isBlank()||this.genre.isBlank()||this.year == 0||this.publisher.isBlank()){
            return true;
        }
        else return false;
    }
    
    public boolean verifyYear(){
        Calendar now = Calendar.getInstance();
        if(year > now.get(Calendar.YEAR)||year < 0){
            return true;
        }
        else return false;
    }
}
