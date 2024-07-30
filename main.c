#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define for_all_tokens(f) \
	f(KEYWORD) \
	f(NAME) \
	f(INTEGER) \
	f(STRING) \

#define for_all_keywords(f) \
	f(FUNCTION) \
	f(IF) \
	f(THEN) \
	f(ELSE) \
	f(LOOP) \
	f(BREAK) \
	f(CONTINUE) \
	f(END) \

#include "main.h"

struct Token
{
	enum TokenType token_type;
	enum KeywordType keyword_type;
	int size;
	char value[];
};

enum KeywordType check_keyword(const char *kw) {
	enum KeywordType i;
	for (i = 0; i < _KW_NONE; i++) {
		if (strcmp(kw, keywords[i]) == 0)
			break;
	}
	return i;
}

int main()
{
	bool again = true;
	bool string_mode = false;
	char buf[128] = {0};
	int i = 0;
	int line = 1;
	int col = 1;
	int sline = 1;
	int scol = 1;
	bool is_num = true;
	while (again) {
		char ch = fgetc(stdin);
		enum TokenType token_type = _TT_NONE;
		if (ch == '\n') {
			col = 1;
			line ++;
		}
		else
			col ++;
		if (!string_mode && (ch == ' ' || ch == '\t' || ch == '\n')) {
			if (i != 0) {
			enum KeywordType j = check_keyword(buf);
			switch (j) {
			case _KW_NONE:
				// not keyword
				break;
			default:
				token_type = TT_KEYWORD;
			}
			if (buf[0] == '"' && buf[i-1] == '"') {
				token_type = TT_STRING;
			} else if (j == _KW_NONE) {
				if (is_num)
					token_type = TT_INTEGER;
				else
					token_type = TT_NAME;
			}
			if (token_type != _TT_NONE)
				fprintf(stdout, "token: %s ", tokens[token_type]);
			if (j != _KW_NONE)
				fprintf(stdout, "keyword: %s ", keywords[j]);
			fprintf(stdout, "string: %s\n", buf); 
			memset(buf, 0, i);
			i = 0;
			is_num = true;
			}
		} else if (ch == EOF) {
			// error?
			if (buf[0] == '"') {
				if (buf[i-1] != '"') {
					fprintf(stderr, "example.txt:%d:%d: error: reached eof\n", sline, scol);
				}
			}
			again = false;
		} else if (!string_mode && (ch >= 'A' && ch <= 'Z')) {
			buf[i++] = ch;
			is_num = false;
		} else if (!string_mode && (ch >= '0' && ch <= '9')) {
			buf[i++] = ch;
		} else if (ch == '"') {
			sline = line;
			scol = col;
			string_mode = !string_mode;
			buf[i++] = ch;
			is_num = false;
		} else if (string_mode) {
			buf[i++] = ch;
		} else {
			// error
			fprintf(stderr, "example.txt:%d:%d: error: unrecognised char\n", line, col);
		}
	}
}
