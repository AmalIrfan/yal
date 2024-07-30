#ifndef for_all_tokens
#error "define for_all_tokens before including main.h"
#endif

#define make_token_type(m) TT_##m,

enum TokenType {
	for_all_tokens(make_token_type)
	_TT_NONE,
};

#undef make_token_type

#define make_token(name) [TT_##name] = #name,

static const char *tokens[] = {
	for_all_tokens(make_token)
};

#undef make_token

#undef for_all_tokens

#ifndef for_all_keywords
#error "define for_all_keywords before including main.h"
#endif

#define make_keyword_type(m) KW_##m,

enum KeywordType {
	for_all_keywords(make_keyword_type)
	_KW_NONE,
};

#undef make_keyword_type

#define make_keyword(name) [KW_##name] = #name,

static const char *keywords[] = {
	for_all_keywords(make_keyword)
};

#undef make_keyword

#undef for_all_keywords
