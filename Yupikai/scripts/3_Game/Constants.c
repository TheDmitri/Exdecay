/*Class that deals with the log system*/
static ref YKLogger g_YKLogger;
static YKLogger GetYKLogger(){
	if (!g_YKLogger) {
		g_YKLogger = new YKLogger();
	}
	return g_YKLogger;
}
