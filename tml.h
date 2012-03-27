/********************
Copyright (C) 2012 Alexander Forselius

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#define QML_PARSER_MODE_ENTITY 0
#define QML_PARSER_MODE_CONTENT 1

#define ENTITY_TOKEN_OBJECT 0
#define ENTITY_TOKEN_PEOPLE 1
#define ENTITY_TOKEN_MONEY 2 
#define ENTITY_OBJECT #
#define ENTITY_PEOPLE @
#define ENTITY_MONEY $
typedef char QML_CHAR;
typedef QML_CHAR *QML_TEXT;
typedef struct qml_node {
    QML_TEXT content;
    QML_TEXT tag;
    char type ; // Node type 
    int iCountChildren ;
    struct qml_node **children;
    struct qml_node *parent; // Parent node
} qml_node;

typedef struct{
    qml_node *documentElement;
} qml_document ;




#endif // MAIN_H_INCLUDED
