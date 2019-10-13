Action()
{	
	web_cleanup_cookies();
	web_cache_cleanup();
	web_cleanup_auto_headers();

	lr_start_transaction("1_transaction");
	
	web_set_max_html_param_len("999999");

	web_url("test.youplace.net", 
		"URL=http://test.youplace.net/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		LAST);

	web_link("Start test", 
		"Text=Start test", 
		"Snapshot=t41.inf", 
		LAST);

	lr_end_transaction("1_transaction",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("refresh");

	web_reg_save_param_ex(
		"ParamName=parse",
		"LB=<form method=\"POST\">",
		"RB=</form>",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
	web_url("1", 
		"URL=http://test.youplace.net/question/1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		LAST);
	
	formsParser();

	lr_end_transaction("refresh",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("submit");

	sendForm();

	lr_end_transaction("submit",LR_AUTO);
return 0;
	lr_think_time(3);
	
	lr_start_transaction("error");

	/* Request with POST method to URL "http://test.youplace.net/question/5" failed during recording. Server response : 406*/

	/* Request with POST method to URL "http://test.youplace.net/question/5" failed during recording. Server response : 406*/

	lr_end_transaction("error",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("success");

	web_url("7", 
		"URL=http://test.youplace.net/question/7", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/question/6", 
		"Snapshot=t38.inf", 
		"Mode=HTML", 
		LAST);

	web_submit_form("7_2", 
		"Snapshot=t39.inf", 
		ITEMDATA, 
		"Name=nBPRbgAFvqGVuVnl", "Value=SZ8haOt2d2oN4", ENDITEM, 
		"Name=LOcFzyNbtdxWGHGf", "Value=test", ENDITEM, 
		LAST);

	lr_end_transaction("success",LR_AUTO);

	return 0;
}

sendForm() {
	int matchCt, ord;
	matchCt = lr_paramarr_len("PStrings");
	
	char *body=lr_eval_string("Body={inputName_1}={inputValue_1}");

	lr_log_message("LOG: %s", body);
	
	web_custom_request("1_2", 
		"URL=http://test.youplace.net/question/1", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/question/1", 
		"Snapshot=t43.inf", 
		"Mode=HTTP", 
		body, 
		LAST);

}