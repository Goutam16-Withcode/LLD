#include <bits/stdc++.h>
using namespace std;

// Abstraction for the document elements
class DocumentElement
{
public:
       virtual string render() = 0;
};

// Concrete implementation for the text elements
class TextElement : public DocumentElement
{
private:
       string text;

public:
       TextElement(string text)
       {
              this->text = text;
       }

       string render() override
       {
              return text;
       }
};

// Concrete implementation for the image elements
class ImageElement : public DocumentElement
{
private:
       string imagePath;

public:
       ImageElement(string imagePath)
       {
              this->imagePath = imagePath;
       }

       string render() override
       {
              return "[Image : " + imagePath + "]";
       }
};

// NewLineElement response a line a break in the document
class NewLineElement : public DocumentElement
{
public:
       string render() override
       {
              return "\n";
       }
};

// TabSpaceElement response a tab space in the document
class TabSpaceElement : public DocumentElement
{
public:
       string render() override
       {
              return "\t";
       }
};

// Document class responsible for holding a collection of the elements
class Document
{
private:
       vector<DocumentElement *> documentElements;

public:
       ~Document()
       {
              for (auto element : documentElements)
              {
                     delete element;
              }
              documentElements.clear();
       }

       void addElement(DocumentElement *element)
       {
              documentElements.push_back(element);
       }

       // Render the document by concatenating the render output of all the elements
       string render()
       {
              string result;
              for (auto element : documentElements)
              {
                     result += element->render();
              }
              return result;
       }
};

// Persistence Interface
class Persistence
{
public:
       virtual void save(string data) = 0;
};

// Filesave implementation of the persistence
class FileSave : public Persistence
{
public:
       void save(string data) override
       {
              ofstream outFile("document.txt");
              if (outFile)
              {
                     outFile << data;
                     outFile.close();
                     cout << "Document saved to document.txt" << endl;
              }
              else
              {
                     cout << "Error : Unable to open file for writing." << endl;
              }
       }
};

// PlaceHolder DBStorage implementation
class DBStorage : public Persistence
{
public:
       void save(string data) override
       {
              // save to DB
       }
};

// DocumentEditor class managing client interactions
class DocumentEditor
{
private:
       Document *document;
       Persistence *storage;
       string renderedDocument;

public:
       ~DocumentEditor()
       {
              delete document;
              delete storage;
       }

       DocumentEditor(Document *document, Persistence *storage)
       {
              this->document = document;
              this->storage = storage;
       }
       void addText(string text)
       {
              document->addElement(new TextElement(text));
              renderedDocument.clear();
       }
       void addImage(string imagePath)
       {
              document->addElement(new ImageElement(imagePath));
              renderedDocument.clear();
       }

       //      Add a new line to the document
       void addNewLine()
       {
              document->addElement(new NewLineElement());
              renderedDocument.clear();
       }
       //      Add a tab Space to the document
       void addTabSpace()
       {
              document->addElement(new TabSpaceElement());
              renderedDocument.clear();
       }

       string renderDocument()
       {
              if (renderedDocument.empty())
              {
                     renderedDocument = document->render();
              }
              return renderedDocument;
       }

       void saveDocument()
       {
              storage->save(renderDocument());
       }
};

// Client uasge example
int main()
{
       Document * document = new Document();
       Persistence * persistence = new FileSave();

       DocumentEditor* editor = new DocumentEditor(document , persistence);
       // Simulate a client using the editor with common text formating features
       editor->addText("Hello, World!");
       editor->addNewLine();
       editor->addText("This is a real-world document editor example");
       editor->addNewLine();
       editor->addTabSpace();
       editor->addText("Indented text after a tab space.");
       editor->addNewLine();
       editor->addImage("picture.jpg");

       // Render and display the final document
       cout<< editor->renderDocument() <<endl;
       editor->saveDocument();
       return 0;
}