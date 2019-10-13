﻿Action()
{

	lr_start_transaction("1_transaction");

	//web_add_cookie("SID=Xq2GlUd4QNkYTyRM6IKX4JkApIQZB41g; DOMAIN=test.youplace.net");
	
	web_set_max_html_param_len("999999");

	web_url("test.youplace.net", 
		"URL=http://test.youplace.net/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		LAST);

	/* Request with GET method to URL "http://test.youplace.net/favicon.ico" failed during recording. Server response : 404*/

	web_link("Start test", 
		"Text=Start test", 
		"Snapshot=t41.inf", 
		LAST);

	/* Request with GET method to URL "http://test.youplace.net/favicon.ico" failed during recording. Server response : 404*/

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
	

{

    char * bufferToSearch = lr_eval_string("{parse}");
    int matchCt, ord;
    char *arrayMemberValue;
    
    //parse all strings with 'p' tag
    lr_save_param_regexp (
        bufferToSearch,
               strlen(bufferToSearch),
               "RegExp=<p>(.+)</p>",
               "Ordinal=All",
               "ResultParam=PStrings",
               LAST );

    matchCt = lr_paramarr_len("PStrings");

    lr_message("%d match(es) found.", matchCt);

    for (ord=1; ord <= matchCt; ord++){
    	
    	arrayMemberValue = lr_paramarr_idx("PStrings", ord);
    	
    	lr_save_int(ord, "ordinal");
    	
	    //Name (ID) of text form
	    lr_save_param_regexp (
	        arrayMemberValue,
	               strlen(arrayMemberValue),
	               "RegExp=<input type=\"text\" name=\"(\\w+)\">",
	               "Ordinal=1",
	               lr_eval_string("ResultParam=inputName_{ordinal}"),
	               LAST );
	    
	    //Name (ID) of select form
	    lr_save_param_regexp (
	        arrayMemberValue,
	               strlen(arrayMemberValue),
	               "RegExp=<select name=\"(\\w+)\">",
	               "Ordinal=1",
	               lr_eval_string("ResultParam=inputName_{ordinal}"),
	               LAST );
	    
	    //Name (ID) of radio form
	    lr_save_param_regexp (
	        arrayMemberValue,
	               strlen(arrayMemberValue),
	               "RegExp=<input type=\"radio\" name=\"(\\w+)\"",
	               "Ordinal=1",
	               lr_eval_string("ResultParam=inputName_{ordinal}"),
	               LAST );

	    
	    //Value of the text form
		//lr_save_string("test", lr_eval_string("inputValue_{ordinal}"));
    }
}


	lr_end_transaction("refresh",LR_AUTO);
return 0;
	lr_think_time(3);

	lr_start_transaction("submit");

	web_submit_form("1_2", 
		"Snapshot=t43.inf", 
		ITEMDATA, 
		"Name=P8OpEZ3u6nIJWlD0", "Value=EhFDVpwEJZdLB", ENDITEM, 
		"Name=tPNvszndA4Hu4MmC", "Value=qbsIRv45TbeeiIU", ENDITEM, 
		"Name=FA0WAMv76WgnxCma", "Value=test", ENDITEM, 
		"Name=SNT9dLaDljWvoOuc", "Value=RRp4lmwMXrFzUXd2", ENDITEM, 
		LAST);

	lr_end_transaction("submit",LR_AUTO);

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