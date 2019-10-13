Action()
{

	lr_start_transaction("1_transaction");

	web_add_cookie("SID=Xq2GlUd4QNkYTyRM6IKX4JkApIQZB41g; DOMAIN=test.youplace.net");

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

	web_url("1", 
		"URL=http://test.youplace.net/question/1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://test.youplace.net/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("refresh",LR_AUTO);

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

	return 0;
}