function formatAvatar(username, url) {
  var img = $("<img/>").attr("src", url).attr("title", username);
  var link = $("<a>").attr("href", "/nodders/"+username)
  img.appendTo(link);
  return link;
}
 

function listAvatar(tweetId, avatar) {
  $.each(avatar, function(k, v) {
    formatAvatar(k, v).prependTo($("div#noddedimgs_"+tweetId));
  });
}

function initNodderImgs() {
  $('div.noddedimgs').hide();
}

function favoriteAction(tweetId) {
  if ($('a#nodbtn_'+tweetId).hasClass('nod')) {
    AJAXcreateFavorite(tweetId);
    $('a#nodbtn_'+tweetId).removeClass('nod');
    $('a#nodbtn_'+tweetId).addClass('nodded');
  } else {
    AJAXdestroyFavorite(tweetId);
    $('a#nodbtn_'+tweetId).removeClass('nodded');
    $('a#nodbtn_'+tweetId).addClass('nod');
  }
}

function createFollow(userId) {
  var r = confirm('Are you sure you want to follow this user?');
  if (r == true) {
    AJAXcreateFollow(userId);
  }
}


function retweet(tweetId) {
  var r = confirm('Are you sure you want to retweet this blurt?');
  if (r == true) {
    AJAXretweet(tweetId);
  }
}

function AJAXcreateFavorite(tweetId) {
  $.ajax({
    type: "GET",
    url: "/create_favorite/"+tweetId,
    success: function(msg){
      postAuthAction(msg);
    }
  });
}

function AJAXdestroyFavorite(tweetId) {
  $.ajax({
    type: "GET",
    url: "/destroy_favorite/"+tweetId,
    success: function(msg){
      postAuthAction(msg);
    }
  });
}

function AJAXcreateFollow(userId) {
  $.ajax({
    type: "GET",
    url: "/create_follow/"+userId,
    success: function(msg){
      postAuthAction(msg);
    }
  });
}


function AJAXretweet(tweetId) {
  $.ajax({
    type: "GET",
    url: "/retweet/"+tweetId,
    success: function(msg){
      postAuthAction(msg);
    }
  });
}

function postAuthAction(msg) {
  if (msg == 'signin') {
    $(location).attr('href', '/signin');
  }
}

function swap_nod_image(tweet_id) {
  var img = $("<img/>").attr("src", "/images/star_yellow.png").addClass("fav-img");
  $("a#fav_"+tweet_id).replaceWith(img);
}
function showNodders(tweetId) {
  $('a#shownodders_'+tweetId).hide();
  $('div#noddedimgs_'+tweetId).show('fast', function() { listAvatar(tweetId, eval('nodders_'+tweetId));});
}
