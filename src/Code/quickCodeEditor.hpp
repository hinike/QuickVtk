#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QTextCursor>
#include <QQuickTextDocument>

namespace quick {

    namespace Code {

        class Highlighter;
        class Errors;

        class Editor : public QObject {
            Q_OBJECT
            Q_PROPERTY(quick::Code::Errors* errors READ getErrors CONSTANT);
            Q_PROPERTY(QQuickTextDocument* document READ getDocument WRITE setDocument NOTIFY documentChanged);
            Q_PROPERTY(QString filePath READ getFilePath NOTIFY filePathChanged);
            Q_PROPERTY(int selectionStart READ getSelectionStart WRITE setSelectionStart NOTIFY selectionStartChanged);
            Q_PROPERTY(int selectionEnd READ getSelectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged);
            Q_PROPERTY(int editorCursor READ getEditorCursor WRITE setEditorCursor NOTIFY editorCursorChanged);
            Q_PROPERTY(int fontSize READ getFontSize NOTIFY fontSizeChanged);
            Q_PROPERTY(int line READ getLine NOTIFY lineChanged);
            Q_PROPERTY(int column READ getColumn NOTIFY columnChanged);
            Q_PROPERTY(bool modified READ getModified WRITE setModified NOTIFY modifiedChanged);
        private:
            static Qml::Register::Controller<Editor> Register;
            QQuickTextDocument* m_document = nullptr;
            Highlighter* m_highlighter = nullptr;
            QString m_filePath;
            bool m_modified = false;
            int minFontSize = 6;
            int maxFontSize = 20;
            int m_selectionStart = 0;
            int m_selectionEnd = 0;
            int m_editorCursor = 0;
            int m_fontSize = 12;
            int m_column = 0;
            int m_line = 0;
        public:
            Editor();
            static Editor* instance;
            static auto Create() -> void;
            auto init() -> void;
            auto getCurrentCursor() -> QTextCursor;
            auto setText(const QString&) -> void;
            auto getText() -> QString;
            auto setFilePath(const QString&) -> void;
            auto getFilePath() -> QString;
            auto setDocument(QQuickTextDocument*) -> void;
            auto getDocument() -> QQuickTextDocument*;
            auto setModified(bool) -> void;
            auto getModified() -> bool;
            auto setFontSize(int) -> void;
            auto getFontSize() -> int;
            auto setSelectionStart(int) -> void;
            auto getSelectionStart() -> int;
            auto setSelectionEnd(int) -> void;
            auto getSelectionEnd() -> int;
            auto setEditorCursor(int) -> void;
            auto getEditorCursor() -> int;
            auto getErrors() -> Errors*;
            auto setLine(int) -> void;
            auto getLine() -> int;
            auto setColumn(int) -> void;
            auto getColumn() -> int;
            auto select(QTextCursor) -> void;
            ~Editor();
        public slots:
            bool onKeyPressed(int, int, const QString&);
            void openFile();
            void saveFile();
            void newFile();
            void increaseFontSize();
            void decreaseFontSize();
            void run();
            void format();
        signals:
            void selectionStartChanged();
            void selectionEndChanged();
            void editorCursorChanged();
            void filePathChanged();
            void modifiedChanged();
            void documentChanged();
            void fontSizeChanged();
            void columnChanged();
            void lineChanged();
            void updateSelection();
        };
    }
}
