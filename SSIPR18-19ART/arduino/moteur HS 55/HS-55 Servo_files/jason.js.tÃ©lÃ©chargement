jQuery( document ).ready(function() {
 
    // If there is just one product image: add class to html so css can hide some stuff
    if(jQuery('.product-img-box .more-views-inner > ul > li').length === 1){
        jQuery('html').addClass('oneImage');
    }
 
    //hide product-tabs-container if it is empty
    if(jQuery('.product-tabs-container > .product_tabs').length <= 0){
        jQuery('.product-tabs-container').hide();
    }
 
    //merge subcategories and products into same Ul so they don't break to separate lines
    if(jQuery('.category-products').length > 0 && jQuery('.apptrian-subcategories').length > 0){
        var li, name, a;
        jQuery('.category-products > ul> li').each(function(index,item,list){
            li = jQuery(item);
            name = li.find('h2').text();
            a = li.find('a:first');
            a.removeClass('product-image');
            li.find('div, h2').not('.saleIcon').remove();
            jQuery('<span>'+name+'</span>').prependTo(a);
        });
        jQuery('.category-products > ul > li').prependTo('.apptrian-subcategories');
    }
 
 
    // allow me to trigger an pseudo event and have it look like a real native event
    // in this case for programatically triggering a change event on the select elements
    Element.prototype.triggerEvent = function(eventName)
    {
            if (document.createEvent)
            {
                    var evt = document.createEvent('HTMLEvents');
                    evt.initEvent(eventName, true, true);
                    return this.dispatchEvent(evt);
            }
            if (this.fireEvent){
                return this.fireEvent('on' + eventName);
            }
    }
 
    jQuery('body').on('click', '.buyTableBtn', function(e){
        e.preventDefault();
        var buyBtn = jQuery(this),
                hash = buyBtn.prop("hash").replace('#',''),
                delayIncrement = 500,
                delay;
 
        var spinner = '<div class="sk-cube-grid">\
        <div class="sk-cube sk-cube1"></div>\
        <div class="sk-cube sk-cube2"></div>\
        <div class="sk-cube sk-cube3"></div>\
        <div class="sk-cube sk-cube4"></div>\
        <div class="sk-cube sk-cube5"></div>\
        <div class="sk-cube sk-cube6"></div>\
        <div class="sk-cube sk-cube7"></div>\
        <div class="sk-cube sk-cube8"></div>\
        <div class="sk-cube sk-cube9"></div>\
        </div>';
        jQuery('body').append('<div id="buyTableBtnMsg">'+spinner+' Adding to Cart...');
 
        window.location.hash = hash;//put the hash in the address bar
        hash = hash.split('&');
        window.scrollTo(0, 0);//scroll to the top of the page
 
        //go through the hash values, look for matching options and set them one-by-one
        jQuery.each(hash,function(index, keyvaluepair){
                delay = index * delayIncrement;
                setTimeout(function(){
                        (function (index, keyvaluepair) {
                            keyvaluepair = keyvaluepair.split('=');
                            var att = keyvaluepair[0],
                                    val = keyvaluepair[1];
 
                            // find the select element;
                            var el = jQuery('#attribute'+att);
 
                            // select the option;
                            el.val(val);
 
                            //trigger the change event
                            $(el.attr('id')).triggerEvent('change');
                        })(index, keyvaluepair);
                         
                    },delay);
        });//end each
 
        delay = delayIncrement * (hash.length+1);
        setTimeout(function(){
            //set quantity to 1
            jQuery('#qty').val('1');
 
            //now that it is configured... add it to the cart
            jQuery('#product-addtocart-button').trigger('click');
        }, delay);
         
    });//end on click event
 
 
    /* Search Results
    –––––––––––––––––––––––––––––––––––––––––––––––––– */
    jQuery('.UI-SEARCH').on('noResults',function(e){
        jQuery('.UI-PLACEHOLDER').show().html('<p class="noResults"><strong>Whoops!</strong> There are no results for that query. Please try again.</p>');
    });
 
    jQuery('.UI-SEARCH').on('notEnoughCharacters',function(e){
        jQuery('.UI-PLACEHOLDER').show().html('<p class="notEnoughCharacters"><strong>Almost There&hellip;</strong>Please type at least 3 characters.</p>');
    });
 
    if(jQuery('body').hasClass('catalogsearch-result-index')){
        //is search page
        if(
            jQuery('.catalogsearch-result-index .searchindex-results').length < 1 && 
            jQuery('.catalogsearch-result-index .searchindex-result').length < 1 &&
            jQuery('.products-grid li').length < 1
        ){
            jQuery('.catalogsearch-result-index .page-title').after('<p class="noResults"><strong>Whoops!</strong> There are no results for that query. Please try again.</p>');
        }
    }
 
    //Allow middle and right clicking on ajax search results to open in new tab
    jQuery('html').on('mousedown','.searchautocomplete-placeholder li[data-url]', function(e){ 
            var el = jQuery(this);
            switch(e.which)
            {
                case 2:
                    //middle Click
                    jQuery('.searchautocomplete-placeholder .active').removeClass('active');//prevents default action
                    window.open(el.attr('data-url'),'_blank');
                    break;
                case 3:
                    //right Click
                    jQuery('.searchautocomplete-placeholder .active').removeClass('active');//prevents default action
                    window.open(el.attr('data-url'),'_blank');
                    break;
            }
 
    });
 
    // since there is live search, if you search and hit enter you are searching twice (extra load on the server)
    // first search is ajax, which won't have time to show up and then it takes you to the search page
    // so let's prevent going to the search page when the user hits enter
    jQuery('.input-text.UI-SEARCH').on('keydown', function(e){
        if (e.keyCode == 13) {
            e.preventDefault();
            e.stopPropagation();
        }
    });
 
    jQuery('.searchautocomplete.UI-SEARCHAUTOCOMPLETE .button').on('click',function(e){
        e.preventDefault();
        e.stopPropagation();
        jQuery('.UI-PLACEHOLDER').show();
            setTimeout(function(){
            jQuery('.UI-PLACEHOLDER').show();
        },150);
    });
     
 
 
    /* Old Gift Certificate Message
    –––––––––––––––––––––––––––––––––––––––––––––––––– */
    jQuery(".error-msg:contains('Gift card') ul").append( "<li><span>If you are trying to use a gift certificate that was issued before July 26th 2016 please contact <a href='mailto:sales@servocity.com'>sales@servocity.com</a></span></li>" );
 
 
     
 
});//end document ready
