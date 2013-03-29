var uservoiceOptions = {
/* required */
key: 'slothnod',
host: 'slothnod.uservoice.com', 
forum: '96659',
showTab: true,  
/* optional */
alignment: 'right',
background_color:'#435326', 
text_color: 'white',
hover_color: '#5d7435',
lang: 'en'
};

function _loadUserVoice() {
var s = document.createElement('script');
s.setAttribute('type', 'text/javascript');
s.setAttribute('src', ("https:" == document.location.protocol ? "https://" : "http://") + "cdn.uservoice.com/javascripts/widgets/tab.js");
document.getElementsByTagName('head')[0].appendChild(s);
}
_loadSuper = window.onload;
window.onload = (typeof window.onload != 'function') ? _loadUserVoice : function() { _loadSuper(); _loadUserVoice(); };
