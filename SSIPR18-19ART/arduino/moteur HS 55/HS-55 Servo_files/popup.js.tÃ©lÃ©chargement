if (typeof Itoris == 'undefined') {
	Itoris = {};
}

Itoris.WishlistPopup = Class.create({
	links: [],
	popup: null,
	config: {},
	clickedLink: null,
	currentCheckbox: null,
	defaultPopupWidth: 0,
	initialize: function(config) {
		this.config = config;
		var obj = this;
		Event.observe(document, 'dom:loaded', function() {
			obj.popup = $('itoris-wishlist-popup-box');
			obj.popup.removeClassName('itoris-wishlist-popup-box-remove');
			obj.addEvents();
			obj.startTrackingLinks();
		});
	},
	startTrackingLinks: function() {
		this.addEventsToWishlistLinks();
		this.tracking = new PeriodicalExecuter(this.addEventsToWishlistLinks.bind(this), 1);
	},
	addEventsToWishlistLinks: function() {
		$$('.itoris-wishlist-popup-box-remove').each(function(elm) {elm.remove()});
		this.addEventsToLinks('/wishlist/index/add/');
		this.addEventsToLinks('/wishlist/index/fromcart/');
		if (this.config.route_name != 'wishlist') {
			this.addEventsToLinks('/' + this.config.route_name + '/index/add/');
			this.addEventsToLinks('/' + this.config.route_name + '/index/fromcart/');
		}
	},
	addEvents: function() {
		Event.observe($('itoris-wishlist-radiostack'), 'keypress', this.selectWishlistByKey.bind(this));
		Event.observe(this.popup.select('.itoris-wishlist-button-cancel')[0], 'click', this.closePopup.bind(this));
		Event.observe(this.popup.select('.itoris-wishlist-button-select')[0], 'click', this.selectWishlist.bind(this));
		var obj = this;
		$$('.itoris-wishlist-radio').each(function(elm){
			if (elm.checked) {
				obj.currentCheckbox = elm;
			}
			Event.observe(elm, 'click', obj.checkWishlist.bind(obj, elm));
		});

		this.popup.show();
		this.defaultPopupWidth = $('itoris-wishlist-popup').getWidth();
		this.popup.hide();
		Event.observe(window, 'resize', function(){
			this.resizePopup(this.defaultPopupWidth);
		}.bind(this));
	},
	resizePopup: function(targetWidth) {
		var popupWindow = $('itoris-wishlist-popup');
		if (document.viewport.getWidth() > targetWidth) {
			popupWindow.style.left = '';
			popupWindow.style.margin = '';
			popupWindow.style.width = '';
		} else {
			popupWindow.style.left = '0';
			popupWindow.style.margin = '0';
			popupWindow.style.width = '100%';
		}
	},
	addEventsToLinks: function(type) {
		var links =  $$('a');
		for (var i = 0; i < links.length; i++) {
			if (links[i].href.indexOf(type) != -1 && this.links.indexOf(links[i]) == -1) {
				if (links[i].onclick) {
					links[i].callback = links[i].onclick;
					links[i].onclick = null;
				}
				this.links.push(links[i]);
				Event.observe(links[i], 'click', this.addToWishlistEvent.bind(this, links[i]));
			}
		}
	},
	addToWishlistEvent: function(link, e) {
		if (this.clickedLink != link) {
			this.showPopup();
			this.clickedLink = link;
			e.stop();
		}
	},
	selectWishlistByKey: function(e) {
		if (e.keyCode == 13) {
			this.selectWishlist();
		}
	},
	checkWishlist: function(elm) {
		this.currentCheckbox = elm;
		if (this.currentCheckbox.value != 'new') {
			$('itoris-wishlist-new-name').value = '';
		}
	},
	validateNewName: function(name) {
		var radios = $$('.itoris-wishlist-radio');
		for (var i = 0; i < radios.length; i++) {
			if (radios[i].alt.toLowerCase() == name) {
				return false;
			}
		}
		return true;
	},
	selectWishlist: function() {
		var error = false;
		var wishlistId = null;
		var isNew = false;
		if (this.currentCheckbox.value == 'new') {
			if ($('itoris-wishlist-new-name').value == '') {
				error = true;
				alert(this.config.message_empty_name);
			} else if (!this.validateNewName($('itoris-wishlist-new-name').value.toLowerCase())) {
				error = true;
				alert(this.config.message_name_exists);
			}
			if (!error) {
				wishlistId = $('itoris-wishlist-new-name').value;
				isNew = true;
				this.prepareLink($('itoris-wishlist-new-name').value, true);
			}
		} else {
			wishlistId = this.currentCheckbox.value;
			this.prepareLink(this.currentCheckbox.value, false);
		}
		if (!error) {
			if (this.config.stay_on_page) {
				this.addProductSilent(wishlistId, isNew);
			} else {
				if (window.opener) {
					setPLocation(this.clickedLink.href, true);
					this.closePopup();
				} else {
					if (this.clickedLink.callback) {
						this.clickedLink.onclick = this.clickedLink.callback;
					}
					if (this.clickedLink.click) {
						this.clickedLink.click();
					} else {
					  var evObj = document.createEvent('MouseEvents');
					  evObj.initEvent( 'click', true, false );
					  this.clickedLink.dispatchEvent(evObj);
					}
					if (this.clickedLink.callback) {
						this.clickedLink.onclick = null;
					}
				}
			}
		}
	},
	prepareLink: function(wishlistId, isNew) {
		var href = this.clickedLink.href;
		href = href.replace(/&?imw(_new)?=[^&]*/gi, '');
		href += href.indexOf('?') == -1 ? '?' : '&';
		href += 'imw=' + encodeURIComponent(wishlistId);
		if (isNew) {
			href += '&imw_new=1';
		}
		this.clickedLink.href = href;
	},
	addProductSilent : function(wishlistId, isNew) {
		var productIdMatch = this.clickedLink.href.match(/\/product\/([0-9]+)/);
		var addPorductId = 0;
		if (productIdMatch) {
			addPorductId = productIdMatch[1];
		}
		var params = {};
		if (this.clickedLink.callback && typeof productAddToCartForm != 'undefined') {
			params = Form.serializeElements(productAddToCartForm.form.select('input,select'), {hash:true})
		}
		params.mwishlist_id = wishlistId;
		params.is_new =  isNew ? 1 : 0;
		params.product = addPorductId;
		$('itoris-wishlist-popup-loading').show();
		new Ajax.Request(this.config.add_product_ajax_url, {
			method: 'get',
			parameters: params,
			onComplete: function(res) {
				var resObj = res.responseText.evalJSON();
				if (resObj.redirect) {
					setLocation(resObj.redirect);
				} else if (resObj.success) {
					this.updateWishlistLink();
					alert(resObj.message);
					this.closePopup();
					$('itoris-wishlist-popup-loading').hide();
				} else {
					alert(resObj.error);
					$('itoris-wishlist-popup-loading').hide();
				}
			}.bind(this)
		});
	},
	updateWishlistLink: function() {
		var wishlistLink = $$('.header a[href|='+ this.config.wishlist_url +']');
		if (wishlistLink.length) {
			new Ajax.Request(this.config.update_wishlist_link_url, {
				onComplete: function(transport) {
					var obj = transport.responseText.evalJSON();
					if (obj.link_text) {
						wishlistLink[0].update(obj.link_text);
					}
				}
			});
		}
	},
	showPopup: function() {
		this.popup.show();
		var obj = this;
		$$('.itoris-wishlist-radio').each(function(elm){
			if (elm.value == obj.mainWishlist) {
				elm.checked = true;
				obj.checkWishlist(elm);
			}
		});
		this.resizePopup(this.defaultPopupWidth);
	},
	closePopup: function() {
		this.popup.hide();
		this.clickedLink = null;
	}
});