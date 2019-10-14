formsParser()
{
	char * bufferToSearch = lr_eval_string("{parse}");
    int matchCt, matchCt2, ord;
    char *arrayMemberValue;
    char *longestValue;
    
    //parse all strings with 'p' tag
    lr_save_param_regexp (
        bufferToSearch,
               strlen(bufferToSearch),
               "RegExp=<p>(.+)</p>",
               "Ordinal=All",
               lr_eval_string("ResultParam=PStrings_{interation}"),
               LAST );

    matchCt = lr_paramarr_len(lr_eval_string("PStrings_{interation}"));

    lr_message("%d match(es) found.", matchCt);

    for (ord=1; ord <= matchCt; ord++){
    	
    arrayMemberValue = lr_paramarr_idx(lr_eval_string("PStrings_{interation}"), ord);
    	
	lr_save_int(ord, "ordinal");
	
	/*
		Map of conditions:
	
		if type of form is text {
			{...}
		} else if type of form is select {
			{...}
		} else if type of form is radio {
			{...}
		} else {
			Another type!
		}
	*/
	
	//=======================
	
    //Name (ID) of text form
    lr_save_param_regexp (
        arrayMemberValue,
               strlen(arrayMemberValue),
               "RegExp=<input type=\"text\" name=\"(\\w+)\">",
               "Ordinal=1",
               lr_eval_string("ResultParam=inputName_{interation}_{ordinal}"),
               LAST );
    
    if( strcmp (lr_eval_string(lr_eval_string("{inputName_{interation}_{ordinal}}")),  lr_eval_string("{inputName_{interation}_{ordinal}}")) != 0 ) {
    	lr_log_message("LOG: This is a text");
		lr_save_string("test", lr_eval_string("inputValue_{interation}_{ordinal}"));
    }
    
    else {
    
    //Name (ID) of select form
    lr_save_param_regexp (
        arrayMemberValue,
               strlen(arrayMemberValue),
               "RegExp=<select name=\"(\\w+)\">",
               "Ordinal=1",
               lr_eval_string("ResultParam=inputName_{interation}_{ordinal}"),
               LAST );
    
   if( strcmp (lr_eval_string(lr_eval_string("{inputName_{interation}_{ordinal}}")),  lr_eval_string("{inputName_{interation}_{ordinal}}")) != 0 ) {
    	lr_log_message("LOG: This is a select");
    	findLongestValue(arrayMemberValue);	    	
    }
    
    else {
    
    
    //Name (ID) of radio form
    lr_save_param_regexp (
        arrayMemberValue,
               strlen(arrayMemberValue),
               "RegExp=<input type=\"radio\" name=\"(\\w+)\"",
               "Ordinal=1",
               lr_eval_string("ResultParam=inputName_{interation}_{ordinal}"),
               LAST );
    	
    if( strcmp (lr_eval_string(lr_eval_string("{inputName_{interation}_{ordinal}}")),  lr_eval_string("{inputName_{interation}_{ordinal}}")) != 0 ) {
    	lr_log_message("LOG: This is a radio");
    	findLongestValue(arrayMemberValue);
    }
    
    else {
    	lr_log_message("LOG: another type");    
    }}}
    
    //======================
    
    }
    
	return 0;
}

findLongestValue(char *arrayMemberValue) {
	
	int matchCt, ord;
	char *longestValue;
	
	//Find the longest value
	lr_save_param_regexp (
	    arrayMemberValue,
	           strlen(arrayMemberValue),
	           "RegExp=value=\"(\\w+)\">",
	           "Ordinal=ALL",
	           lr_eval_string("ResultParam=selectValues"),
	           LAST );
	
	matchCt = lr_paramarr_len("selectValues");
	longestValue = "";
	
	for (ord=1; ord <= matchCt; ord++){
		if (strlen (lr_paramarr_idx("selectValues", ord)) > strlen(longestValue)) {
			longestValue = lr_paramarr_idx("selectValues", ord);
		}
	}
	
	lr_save_string(longestValue, lr_eval_string("inputValue_{interation}_{ordinal}"));
	
	return 0;
	
}

bodyRequestBuilder() {
	int matchCt, ord;
	char *body=lr_eval_string(lr_eval_string("Body={inputName_{interation}_1}={inputValue_{interation}_1}"));
	matchCt = lr_paramarr_len(lr_eval_string("PStrings_{interation}"));
	
	for (ord=2; ord < matchCt; ord++){
		lr_save_int(ord, "ordinal");
		snprintf( body, 2014 , "%s&%s", body, lr_eval_string(lr_eval_string("{inputName_{interation}_{ordinal}}={inputValue_{interation}_{ordinal}}")) );
	}

	lr_log_message("LOG: %s", body);
	
	lr_save_string(body, "submitFormBody");
}