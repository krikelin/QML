/********************
Copyright (C) 2012 Alexander Forselius

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
********************/
#include "tml.h"
#include <stdlib.h>
/*char *append_string(QCHAR *buffer, QCHAR *newTokens, int extra) {
    int size = sizeof(buffer) *sizeof(QCHAR);
    int newSize = extra + size;
    QCHAR *newBuffer = (QCHAR *)malloc(newSize * sizeof(QCHAR));
    for(int i = 0; i < size ; i++) {
        newBuffer[i] = buffer[i];
    }
    for(int i = 0; i < sizeof(newTokens) * extra; i++ ) {
        newBuffer[i + size] = newTokens[i];
    }
    free(buffer); // delete buffer
}*/
int x = 0;
/***
Creates a QML Text container
****/
QML_TEXT createQMLText(int iChSize) {
    QML_TEXT text = (QML_TEXT)malloc(iChSize * sizeof(QML_CHAR));
    memset(text, 0, iChSize * sizeof(QML_CHAR));
    text[0] = '\0';
    return text;
}
/***
Creates a QMLElement in the memory
***/
qml_node *createQMLElement() {
    qml_node *child = (qml_node *)malloc(1 * sizeof(qml_node));
    memset(child, 0, sizeof(qml_node));
    child->children = (qml_node *)malloc(100 * sizeof(qml_node));
    child->iCountChildren = 0;
    child->tag = createQMLText(255);
    child->content = createQMLText(1255);
    return child;
}
/***
Push a child to the qml_node
**/
void qml_push_child(qml_node *container, qml_node *child) {
    container->iCountChildren++;
    container->children[container->iCountChildren] = child;
}
size_t getTextLength(char *text) {
    size_t i = 0;
    char ch = ' ';
    while((ch = text[i++]) != '\0') ;
    return i;
}
qml_document *parseQML(QML_TEXT text,int unicode) {
    int row = 0;
    int col = 0;
    int mode = QML_PARSER_MODE_ENTITY;
    int level = 0;
    qml_node *currentNode = NULL;
    qml_document *qmlDoc = (qml_document *)malloc(1 * sizeof(qml_document));

    int textPos = 0;
    int length = getTextLength(text);
    for(int i = 0; i < length; i++) {
        
        QML_CHAR token = text[i];
        switch(token) {
            case '\n':
                row++;
                col = 0;
                break;
            case '#':
            case '@':
            case '$':
            case '^':
                textPos = 0;
                level--;
                mode = QML_PARSER_MODE_ENTITY;
                qml_node *child = createQMLElement();
                
                // add current_node to children
                if(currentNode != NULL) {
                    currentNode->children[currentNode->iCountChildren] = child; // Add children to collection
                    currentNode->iCountChildren++; // Increase it
                    child->parent = currentNode;
                    qml_push_child(currentNode, child);
                } else {
                    qmlDoc->documentElement = child;
                }   
                currentNode = child;
                child->type = token;
                
                break;
            case ';':
                if(currentNode->parent == NULL && level < 0) {
                   
                    printf("Invalid token at row %d, column %d", row, col);
                    return NULL;
                }
                mode = QML_PARSER_MODE_ENTITY;
                currentNode = currentNode->parent;
                level++;
                
                // Reset text buffer
                char *content = currentNode->content;
                textPos = 0;
                break;
            default:
                switch(mode) {
                    case QML_PARSER_MODE_ENTITY:
                        if(token == ' ' || token == '\t') {
                            mode = QML_PARSER_MODE_CONTENT;
                            textPos = 0;
                            break;
                        }
                        else {      
                            char *text = currentNode->tag;    
                            currentNode->tag[textPos] = token;
                                
                        }
                        textPos++;
                        break;
                    case QML_PARSER_MODE_CONTENT:
                        currentNode->content[textPos] = token;
                        char *content = currentNode->content;
                        textPos++;
                        break;
                
                }
            break;
                
        }
        if(level != 0) {
//            cerr("Error in leveling");
        }
        
        // insert code here
    }
    return qmlDoc;
}

