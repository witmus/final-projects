/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tests;

import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.ValueSource;
import pl.polsl.lab.biblioteka.model.Book;
import pl.polsl.lab.biblioteka.model.Library;
import pl.polsl.lab.biblioteka.model.Library.AddBookIncompleteDataException;
import pl.polsl.lab.biblioteka.model.Library.InvalidYearException;

/**
 *
 * @author Witold Muszyński
 * @version 1.0
 */
public class LibraryTest {
    
    /**
     * Library model for testing
     */
    private Library testLibrary;
    
    @BeforeEach
    public void setUp(){
        testLibrary = new Library();
        testLibrary.LoadBooksFromFile("testBooks.txt");
        testLibrary.LoadUsersFromFile("testUsers.txt");
    }
    
    @AfterEach
    public void clear(){
        testLibrary = null;
    }
    
    /**
     * Try getting a book object with an invalid index from the arraylist.
     * @result catching all IndexOutOfBounds exceptions
     * @param arg Book index
     */
    @ParameterizedTest
    @ValueSource(ints = {-1, 3, 4})
    public void testGetByIdOutOfBounds(int arg){
        try{
            testLibrary.getBookById(arg);
            fail();
        }
        catch(IndexOutOfBoundsException e){
            
        }
    }
    
    /**
     * Get a book object from the edges of the arraylist.
     * @result Correct return of book objects
     * @param arg Book index
     */
    @ParameterizedTest
    @ValueSource(ints = {0, 2})
    public void testGetByIdEdges(int arg){
        try{
            testLibrary.getBookById(arg);
        }
        catch(ArrayIndexOutOfBoundsException e){
            fail();
        }
    }
    
    /**
     * Try removing a book with an invalid index from the arraylist.
     * @result catching all IndexOutOfBounds exceptions
     * @param arg Book index
     */
    @ParameterizedTest
    @ValueSource(ints = {-1, 3, 4})
    public void testRemoveOutOfBounds(int arg){
        try{
            testLibrary.RemoveBook(arg);
            fail();
        }
        catch(IndexOutOfBoundsException e){
            
        }
    }
    
    /**
     * Remove a book object from the edge of the arraylist.
     * @result Correct removal of book objects
     * @param arg Book index
     */
    @ParameterizedTest
    @ValueSource(ints = {2, 0})
     public void testRemoveFromEdges(int arg){
        try{
            testLibrary.RemoveBook(arg);
        }
        catch(ArrayIndexOutOfBoundsException e){
            fail();
        }
    }
     
     /**
     * Try adding Books with incomplete data to the arraylist.
     * @result Catching all AddBookIncompleteData exceptions.
     * @CsvSource Each line corresponds to a singular book object.
     */
    @ParameterizedTest
    @CsvSource({
        "'','','',''",
        "'',a,a,a",
        "a,'',a,a",
        "a,a,'',a",
        "a,a,a,''"
    })
    public void testAddBookWithNulls(String title, String author, String publisher, String genre){
        try{
            Book testBook = new Book(title, author, publisher, 1, 1, genre, true);
            testLibrary.AddBook(testBook);
            fail();
        }
        catch(AddBookIncompleteDataException e){
            
        }
    }
    
    /**
     * Try adding a book with an invalid year of publishment to the arraylist.
     * @result Catching all InvalidYear exceptions.
     * @param year Examples of unrealistic publishment years
     */
    @ParameterizedTest
    @ValueSource(ints = {-1, -200, 2021, 5000})
    public void testAddBookWithInvalidYear(int year){
        try{
            Book testBook = new Book("a", "a", "a", year, 1, "a", true);
            testLibrary.AddBook(testBook);
            fail();
        }
        catch(InvalidYearException e){
            
        }
    }
    
    /**
     * Try signing in with an invalid pair of username and password.
     * @result Returning false each time input data is invalid..
     * @CsvSource Each line corresponds to a singular user.
     */
    @ParameterizedTest
    @CsvSource({
        "d,d",
        "a,b",
        "a,d",
        "d,a"
    })
    public void testUsers(String username, String password){
        assertFalse(testLibrary.verifyUser(username, password));
    }
}
