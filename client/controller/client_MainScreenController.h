#ifndef CLIENT_EVENTS_CLIENT_MAINSCREENCONTROLLER_H_
#define CLIENT_EVENTS_CLIENT_MAINSCREENCONTROLLER_H_

#include <iostream>
#include <gtkmm.h>

/**
  * Im gonna copy as much as I can the Android MVC + everything I can
  * (eg Use of callbacks from user responses)
  *
  * Since this is mega fast sonic gotta go fast coding Im not gonna do
  * .cpp files and the MVC pattern im prolly gonna implement it in a
  * whole .h file for making include's problems dissappear
  */

/* ---------------------- OTHERS ---------------------- */

/**
 * Simple interface, nothing weird to comment about it
 */
class OnEnterPressedInterface {
public:
  virtual void onEnterPressed(Gtk::Entry *editText) = 0;
};

enum MainScreenResult { RESULT_ERROR, RESULT_INDETERMINATE, RESULT_OK };

/* ---------------------- VIEW ---------------------- */

#define PATH_EDIT_TEXT_VIEW "client_home_screen_edit_text"
#define PATH_PROGRESS_BAR_VIEW "client_home_screen_progress_bar"
#define PATH_RESULT_TEXT_VIEW "client_home_screen_result_text_view"

class MainScreenView : public Gtk::Window {
private:
    Gtk::Entry *editText = nullptr;
    Gtk::Spinner *progressBar = nullptr;
    Gtk::Label *resultText = nullptr;
    OnEnterPressedInterface *callback = NULL;

    /**
     * Simple method that justs dispatches to the interface if exists
     * Else its default behaviour its nothing
     */
    void onEnterPressed(Gtk::Entry *editText) {
      if (callback)
        callback->onEnterPressed(editText);
    }

    void setProgressBarIndeterminate(bool active) {
      if (active)
        progressBar->start();
      else progressBar->stop();
    }

public:
  MainScreenView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder) :
          Gtk::Window(cobject) {
    refBuilder->get_widget(PATH_EDIT_TEXT_VIEW, editText);
    refBuilder->get_widget(PATH_PROGRESS_BAR_VIEW, progressBar);
    refBuilder->get_widget(PATH_RESULT_TEXT_VIEW, resultText);

    if(editText)
      editText->signal_activate().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MainScreenView::onEnterPressed), editText));
  }

  virtual ~MainScreenView() {}

  /**
   * Setter if someone wants to do something about the Enter pressing
   */
  void setOnEnterPressedListener(OnEnterPressedInterface *listener) {
    callback = listener;
  }

  void setResult(MainScreenResult result) {
    switch (result) {
      case RESULT_OK:
        setProgressBarIndeterminate(false);
        resultText->set_text("CONNECTED");
        break;

      case RESULT_INDETERMINATE:
        setProgressBarIndeterminate(true);
        resultText->set_text("");
        break;

      case RESULT_ERROR:
        setProgressBarIndeterminate(false);
        resultText->set_text("AN ERROR HAS OCCURED. PLS TRY AGAIN");
    }
  }
};

/* ---------------------- CONTROLLER ---------------------- */

#define PATH_LAYOUT "res/layout/home_screen.glade"
#define PATH_ROOT_VIEW "client_home_screen_root_view"

class MainScreenController : private OnEnterPressedInterface {
private:
  MainScreenView *view;

  /**
  * Has private inheritance. Why should any class know i can handle this
  * Since this is something internal of this controller, I think its ok
  */
  virtual void onEnterPressed(Gtk::Entry *editText) {
    view->setResult(RESULT_INDETERMINATE);
  }

public:
  /**
   * I should create a generic Controller class that already has this method
   */
  Gtk::Window * getView() { return view; };

  virtual ~MainScreenController() { }

  /**
   * Create builder, parse xml, delegate inflate responsibility, set callbacks
   */
  MainScreenController() : view(nullptr) {
    auto refBuilder = Gtk::Builder::create();

    try {
      refBuilder->add_from_file(PATH_LAYOUT);
    } catch(const Glib::FileError& ex) {
      std::cout << "FileError: " << ex.what() << std::endl;
      return;
    } catch(const Glib::MarkupError& ex) {
      std::cout << "MarkupError: " << ex.what() << std::endl;
      return;
    } catch(const Gtk::BuilderError& ex) {
      std::cout << "BuilderError: " << ex.what() << std::endl;
      return;
    }

    refBuilder->get_widget_derived(PATH_ROOT_VIEW, view);

    view->setOnEnterPressedListener(this);
  }
};

#endif /* CLIENT_EVENTS_CLIENT_MAINSCREENCONTROLLER_H_ */
