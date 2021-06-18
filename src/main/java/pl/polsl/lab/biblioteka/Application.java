/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.biblioteka;

import pl.polsl.lab.biblioteka.controller.LibraryController;
import pl.polsl.lab.biblioteka.model.Library;
import pl.polsl.lab.biblioteka.view.AddBookView;
import pl.polsl.lab.biblioteka.view.LibraryView;
import pl.polsl.lab.biblioteka.view.LogInRegisterView;

/**
 *
 * @author Witold
 * @version 1.1
 */
public class Application {
    public static void main(String[] args) {
        Library library = new Library();
        library.LoadBooksFromFile("books.txt");
        library.LoadUsersFromFile("users.txt");
        LibraryView libView = new LibraryView();
        libView.loadBooksList(library.getBooksList());
        AddBookView addView = new AddBookView();
        LogInRegisterView logInView = new LogInRegisterView();
        LibraryController libController = new LibraryController(libView, addView, library, logInView);
        libView.setLocationRelativeTo(null);
        addView.setLocationRelativeTo(null);
        logInView.setLocationRelativeTo(null);
        logInView.setVisible(true);
    }
}
