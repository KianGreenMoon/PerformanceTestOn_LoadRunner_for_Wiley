Action()
{	
	int i;
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
	
	for (i = 1; i <= 50; i++) {
		
	lr_save_int(i, "interation");

	lr_start_transaction("refresh");

	web_reg_save_param_ex(
		"ParamName=parse",
		"LB=<form method=\"POST\">",
		"RB=</form>",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
	web_url("1", 
		"URL=http://test.youplace.net/question/{interation}", 
		"Resource=0", 
		"RecContentType=text/html", 
		//"Referer=http://test.youplace.net/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		LAST);
	
	formsParser();

	lr_end_transaction("refresh",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("submit");

	bodyRequestBuilder();
	
	web_reg_find("Search=Body",
	    "SaveCount=succes_count",
		"Text=Test successfully passed",
		LAST);
	web_reg_find("Search=Body",
	    "SaveCount=error_count",
		"Text=ERROR: one or several values are incorrect",
		LAST);
	
	web_custom_request("1_2", 
		"URL=http://test.youplace.net/question/{interation}", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/question/{interation}", 
		"Snapshot=t43.inf", 
		"Mode=HTTP", 
		lr_eval_string("{submitFormBody}"),
		LAST);
	
	if(atoi ( lr_eval_string("{succes_count}") ) > 0) {
		lr_end_transaction("submit", LR_PASS);
		return 0;
	}
	else if(atoi ( lr_eval_string("{error_count}") ) > 0) {
		lr_end_transaction("submit", LR_FAIL);
		return 0;
	}

	lr_end_transaction("submit",LR_AUTO);
	
	}
	
	return 0;
}