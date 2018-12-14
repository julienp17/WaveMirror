function image(e){
    var files = !!e.files ? e.files : [];
    
    if(!files.length || !window.FileReader) return; // no file selected, or no FileReader support
            
            if (/^image/.test( files[0].type)){ // only image file
                var reader = new FileReader(); // instance of the FileReader
                reader.readAsDataURL(files[0]); // read the local file
       
                reader.onloadend = function(){ // set image data as background of div
                    e.parentNode.style.background = "url("+this.result+")";
                    e.parentNode.style.backgroundSize = "cover";
                    e.parentNode.setAttribute("class", "imagePreview ui-sortable-handle active");
                    var d1 = document.getElementById('sortableImages');
                    d1.insertAdjacentHTML('beforeend', '<li class="imagePreview neutral"><span onclick="this.parentNode.remove()" class="close"></span><input onchange="image(this)" class="uploadFile" type="file" name="image[]" class="img" /><input name="galleryOrder[]" type="text" value="image-new" /></li>');
                
                }
            }
}
function video(e){
    var files = !!e.files ? e.files : [];

    var allowedExts = ["video/mp4"];
    if(!files.length || !window.FileReader) return; // no file selected, or no FileReader support
            
            if(allowedExts.indexOf(files[0].type) != -1)
            {
                var reader = new FileReader(); // instance of the FileReader
                reader.readAsDataURL(files[0]); // read the local file
       
                reader.onloadend = function(){ // set image data as background of div
                    
                    
                    e.parentNode.setAttribute("class", "videoPreview ui-sortable-handle active");
                    var d1 = document.getElementById('sortableImages');
                    d1.insertAdjacentHTML('beforeend', '<li class="videoPreview neutral"><span onclick="removeItem(this)" class="close"></span><input onchange="video(this)" class="uploadVideo" type="file" name="video[]" class="img" /><input name="galleryOrder[]" type="text" value="video-new" /></li>');
                    var node = document.createElement("span"); 
                    node.setAttribute("class","name");
                    var textnode = document.createTextNode(files[0].name);         // Create a text node
                    node.appendChild(textnode);  
                    e.parentNode.appendChild(node); 
                    
                }
            }
}
function removeImage(e,id){
    e.parentNode.remove();
    var form = document.getElementById('submitProject');
    if(id)
        form.insertAdjacentHTML('beforeend', '<input type="hidden" name="removeImage[]" value="'+id+'"/>');
}
function removeVideo(e,id){
    e.parentNode.remove();
    var form = document.getElementById('submitProject');
    if(id)
        form.insertAdjacentHTML('beforeend', '<input type="hidden" name="removeVideo[]" value="'+id+'"/>');
}
jQuery(document).ready(function ($) {

    if($('.product-shop').length)
    {
        var height = $('.product-shop').height();
        height = height - 30;
        $('.product-image').css('min-height',height+'px');
    }
    

    //*update the product SKU

    $('.catalog-product-view #product-options-wrapper dd select').on('change',function(){
        
        var selectedAttributeId = $(this).val();
        var confAttributeId = $(this).attr('attribute');
        var productsIds = new Array();
        var hashArray = new Array();

        if (selectedAttributeId) 
        {
            
            
            $('.catalog-product-view #product-options-wrapper .row').each(function(){
                var confAttributeId = $('select',$(this)).attr('attribute');
                var selectedAttributeId = $('select',$(this)).val();
                
                if(selectedAttributeId){
                    if(typeof spConfig != 'undefined')
                        productsIds.push(getProductIds(confAttributeId, selectedAttributeId));
                
                    //generate hash
                    hashArray.push(confAttributeId+'='+selectedAttributeId);
                }
            });

            var sku = containsAll.apply(this, productsIds);
            
            if(sku.length == 1)
            {
                $("#skuInfoSimpleProduct").html(productMap[sku]);
		if (productAvailability[sku] == 1){
                        $(".product-shop .availability").removeClass('out-of-stock');
			$(".product-shop .availability").addClass('in-stock');
			$(".product-shop .availability .row > span").text('In stock');
		} else {
                        $(".product-shop .availability").removeClass('in-stock');
			$(".product-shop .availability").addClass('out-of-stock');
                        $(".product-shop .availability .row > span").text('Out of stock');
		}
                document.getElementById("skuInfoSimpleProduct").style.display = "block";
                document.getElementById("skuInfo").style.display = "none";
            }
            else{
                document.getElementById("skuInfoSimpleProduct").style.display = "none";
                document.getElementById("skuInfo").style.display = "block";
            }
        }
        else
        {
            document.getElementById("skuInfoSimpleProduct").style.display = "none";
            if($('#skuInfo').html() != '')
             document.getElementById("skuInfo").style.display = "block";
        }
        //change hash
        var hash = hashArray.join('&');
        window.location.hash = '#'+hash;

    });
    function getProductIds (confAttributeId, selectedAttributeId){
        var options = spConfig.config.attributes[confAttributeId].options;
        
        var productIds = options.find(function (option) {return option.id == selectedAttributeId}).products;
        
        return productIds;
    }

    function containsAll() {
        var output = [];
        var cntObj = {};
        var array, item, cnt;
        // for each array passed as an argument to the function
        for (var i = 0; i < arguments.length; i++) {
            array = arguments[i];
            // for each element in the array
            for (var j = 0; j < array.length; j++) {
                item = "-" + array[j];
                cnt = cntObj[item] || 0;
                // if cnt is exactly the number of previous arrays, 
                // then increment by one so we count only one per array
                if (cnt == i) {
                    cntObj[item] = cnt + 1;
                }
            }
        }
        // now collect all results that are in all arrays
        for (item in cntObj) {
            if (cntObj.hasOwnProperty(item) && cntObj[item] === arguments.length) {
                output.push(item.substring(1));
            }
        }
        return(output);
    } 



    //*END update the product SKU

    function addVideo()
    {
        $('.videoPreview.neutral .uploadVideo').on('click',function(){
            var videoBoxInput = '<div class="blackOverlay"></div><div class="addVideoBox"><div class="breadcrumbs"><span class="fristStep active">1. Source selection</span> - <span class="secondStep">2. Submit URL</span></div><div class="selectSource"><span class="yt"></span><span class="vimeo"></span></div><div class="inputWrap"><input type="text" placeholder="e.g: https://www.youtube.com/watch?v=oUyWUMWFFuU" name="youtubelink" value=""/><span class="addYtLink">Add</span><span class="cancelLink">Cancel</span></div></div>';
            $('body').append(videoBoxInput);

            $('.addVideoBox .selectSource .yt, .addVideoBox .selectSource .vimeo').on('click',function(){
                $('.selectSource').css('display','none');
                $('.breadcrumbs span').removeClass('active');
                $('.breadcrumbs span.secondStep').addClass('active');
                $('.addVideoBox .inputWrap input, .addVideoBox .inputWrap .addYtLink ').css('display','inline-block');

                if($(this).hasClass('vimeo'))
                {
                    $('.addVideoBox .inputWrap input').attr('placeholder', 'e.g.: https://vimeo.com/12345678');
                    $('.addVideoBox .inputWrap span.addYtLink').switchClass( "addYtLink", "addVimeoLink", 0);
                }
                addVideoURLs();
            });


            $('.cancelLink').on('click',function(){
                $('.addVideoBox, .blackOverlay').remove();
            });
        });
    }
    function addVideoURLs(){
        $('.addYtLink').on('click',function(){
                var ytLinkValue = $('.addVideoBox input').val();
                var regExp = /^.*(youtu.be\/|v\/|u\/\w\/|embed\/|watch\?v=|\&v=|\?v=)([^#\&\?]*).*/;
                var match = ytLinkValue.match(regExp);
                if (match && match[2].length == 11) {
                    var activeInput = $('.videoPreview.neutral .uploadVideo');
                    activeInput.attr('value',ytLinkValue);
                    activeInput.parent().removeClass('neutral');
                    activeInput.parent().addClass('active');
                    activeInput.parent().append('<span style="background: url(http://img.youtube.com/vi/'+match[2]+'/1.jpg); background-size:cover;" class="thumbnail"></span>');
                    $('#sortableImages').append('<li class="videoPreview neutral"><span onclick="this.parentNode.remove()" class="close"></span><input class="uploadVideo" type="text" name="video[]" class="img"  value=""/></li>');
                    $('.addVideoBox, .blackOverlay').remove();
                    addVideo();
                }
                else
                {
                    alert('YouTube link is incorrect.');
                    return false;
                }
            });
            $('.addVimeoLink').on('click',function(){
                var vimeoLinkValue = $('.addVideoBox input').val();
                var regExp =  regExp = /^.*(vimeo\.com\/)((channels\/[A-z]+\/)|(groups\/[A-z]+\/videos\/))?([0-9]+)/;
                var match = vimeoLinkValue.match(regExp);
                if (match) {
                    var activeInput = $('.videoPreview.neutral .uploadVideo');
                    activeInput.attr('value',vimeoLinkValue);
                    activeInput.parent().removeClass('neutral');
                    activeInput.parent().addClass('active');

                    /*get vimeo thumbnail*/
                    vimeoLoadingThumb(match[5],activeInput);
                
                    /*end get vimeo thumbnail*/
                    
                    $('#sortableImages').append('<li class="videoPreview neutral"><span onclick="this.parentNode.remove()" class="close"></span><input class="uploadVideo" type="text" name="video[]" class="img"  value=""/></li>');
                    $('.addVideoBox, .blackOverlay').remove();
                    addVideo();
                }
                else
                {
                    alert('Vimeo link is incorrect.');
                    return false;
                }
            });
    }
    addVideo();

    function vimeoLoadingThumb(video_id,activeInput){    
        $.ajax({
            type:'GET',
            url: 'http://vimeo.com/api/v2/video/' + video_id + '.json',
            jsonp: 'callback',
            dataType: 'jsonp',
            success: function(data){
                var thumbnail_src = data[0].thumbnail_medium;
                
                activeInput.parent().append('<span style="background: url('+thumbnail_src+'); background-size:cover;" class="thumbnail"></span>');
            }
        });
            
      
    }


    $( "#sortable" ).sortable({handle: '.handle'});

    $('.addPart').on('click',function(){
        $('ul#sortable').append('<li><input class="quantityField" type="text" name="qty[]" placeholder="QTY..."/><input class="numberField" type="text" name="part[]" placeholder="Part Number..."/><input class="nameField" type="text" name="partname[]" placeholder="Description..."/><input class="linkField" type="text" name="link[]" placeholder="External Link..."/><span class="sortableHandle handle"></span><span class="removePart"></span></li>');
        
        $('.removePart').on('click',function(){
            $(this).parent().remove();
        });
        return false;
    });
    $('.removePart').on('click',function(){
            var id = $(this).attr('data-id');
            $('form#submitProject').append('<input type="hidden" name="removeParts[]" value="'+id+'"/>');
            $(this).parent().remove();
        });
    

    $( "#sortableImages" ).sortable({
        stop: function(event, ui) {
          $(this).find('.neutral').appendTo(this);
        }
    });
    if($('.projects-submitproject-index').length)
        CKEDITOR.config.removePlugins = 'about';
    function validateSubmiProject()
    {
        $('.validationInfo').remove();
        var flag = false;
        var name = $('#submitProject .name .required').val();
        if(name == ""){
            $('.errorMessages').append('<p class="validationInfo red">The name field can not be empty.</p>');
            flag = true;
        }
        var img = $('#submitProject .imagePreview .required').val();    
        if(img == ""){
            $('.errorMessages').append('<p class="validationInfo red">The image has to be uploaded.</p>');
            flag = true;
        }
        

        $('#submitProject .quantityField').each(function(){
            if($(this).val() == "")
            {
                $('.errorMessages').append('<p class="validationInfo red">The quantity field can not be empty.</p>');
                flag = true;
            }
        });
        $('#submitProject .nameField').each(function(){
            if($(this).val() == "")
            {
                $('.errorMessages').append('<p class="validationInfo red">The part name field can not be empty.</p>');
                flag = true;
            }
        });

        return flag;
    }
    $('#submitProject input[type="submit"]').on('click',function(e){
        
        if(validateSubmiProject() == true)
            e.preventDefault();
       
    });

        if($('.projects-index-index .tabsWrap a img').attr('id') == 'yt')
        {
            $('.projects-index-index .tabsWrap a img#yt').parent().append('<span class="playVideo"></span>');            
        }

    $('.bumpit').on('click',function(){
            if($(this).hasClass('noactive')) return false;

            if(!$(this).hasClass('bumped'))
            {
                var url = bfmajaxcartposturl + 'projects/view/bumpItAjax';
                var action = 1;
            }
            else
            {
                var url = bfmajaxcartposturl + 'projects/view/unBumpItAjax';
                var action = 0;
            }
            
            $.ajax({
                    url: url,
                    type: 'post',
                    success: function (d) {
                        if(d)
                        {
                            var bumps = $('.bumps span').text();
                            if(action == 1)
                            {
                                bumps++;
                                $('.bumpit').addClass('bumped');
                                $('.bumpit').text('BUMPED');
                            }
                            else
                            {
                                $('.bumpit').removeClass('bumped');
                                $('.bumpit').text('BUMP IT');
                                bumps--;
                            }
                            if(bumps == 1)
                                $('.bumps').html('<span>'+bumps+'</span> BUMP');
                            else
                                $('.bumps').html('<span>'+bumps+'</span> BUMPS');
                        }
                    }
            });   

        return false;
    });

    $('.addPartsToCart').on('click',function(){
        
        var url = bfmajaxcartposturl + 'projects/view/addToCartAjax';

                
            $.ajax({
                    url: url,
                    type: 'post',
                    success: function (d) {
                        window.location.replace("/checkout/cart/");
                    }
            });

            return false;
    });
    $('.tabsMenu div').on('click',function(){
         var tabname = $(this).attr('id');
         var text = $(this).text();
         $('.tabcontent, .tabsMenu div').removeClass('active');
         $(this).addClass('active');
         $('.tab-'+tabname).addClass('active');
         $('.tabsWrap .activeElem span').text(text);
        
    });

    $('.loadMoreProjects').on('click',function(){

        var url = bfmajaxcartposturl + 'projects/index/loadProjectsAjax';
        var type = $(this).attr('rel');
        $(this).addClass('active');
        $('.loader', $(this)).css('display','block');
        var projectsAmount = $('.lastProjectsWrap .project', $('.loadMoreProjects.active').parent().parent()).length;
        var page = Math.ceil(projectsAmount/4); 
       
        $.ajax({
            url: url,
            type: 'post',
            data: { type: type, page: page},
            success: function (d) {
                if(d != 'nomore')
                {
                    $('.lastProjectsWrap', $('.loadMoreProjects.active').parent().parent()).append(d);
                
                    $('.loader').css('display','none');
                    $('.loadMoreProjects').removeClass('active');
                }
                else
                {
                    $('.nomoreprojects', $('.loadMoreProjects.active').parent()).css('display','block');
                    $('.loader').css('display','none');
                    $('.loadMoreProjects.active').css('display','none');
                    $('.loadMoreProjects').removeClass('active');
                }
            }
        });

        return false;
    });

//MAIN SLIDESHOW
	$('#slider .bfm-slideshow-container>ul.slideshow').responsiveSlides({
        auto: true, // Boolean: Animate automatically, true or false
        speed: 700, // Integer: Speed of the transition, in milliseconds
        timeout: 50000, // Integer: Time between slide transitions, in milliseconds
        pager: true, // Boolean: Show pager, true or false
        nav: true, // Boolean: Show navigation, true or false
        random: false, // Boolean: Randomize the order of the slides, true or false
        pause: false, // Boolean: Pause on hover, true or false
        pauseControls: true, // Boolean: Pause when hovering controls, true or false
        prevText: "«", // String: Text for the "previous" button
        nextText: "»", // String: Text for the "next" button
        //maxwidth: "1400", // Integer: Max-width of the slideshow, in pixels
        navContainer: "", // Selector: Where controls should be appended to, default is after the 'ul'
        manualControls: ".unique-pager", // Selector: Declare custom pager navigation
        namespace: "bfm-slides", // String: Change the default namespace used
        before: function () {
      

        }, // Function: Before callback
        after: function () {
          
        } // Function: After callback
    });
	

    // gallery images 
    $(document).on('click', '.more-views ul>li>a', function (e) {
        e.preventDefault();
        e.stopPropagation();
        if($(this).parent().hasClass('video'))
        {
            var video = $(this).attr('dataimg');
            $('.image-normal img').css('display','none');
            $('.image-normal #video').remove();
            //$('.image-normal').append('<video id="video" controls="controls"><source src="'+video+'" /></video><div class="clear"></div>');
            
            
            if(video.length != 11)
                $('.image-normal').append('<iframe id="video" src="https://player.vimeo.com/video/'+video+'" width="546" height="409" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe><div class="clear"></div>');
            else
                $('.image-normal').append('<iframe id="video" width="546" height="409" src="https://www.youtube.com/embed/'+video+'?autoplay=1&rel=0" frameborder="0"></iframe><div class="clear"></div>');
        }
        else{
            $('.image-normal #video').remove();
            $('.image-normal img').css('display','block');
        }
        //destroy zoom
        // if($('.catalog-product-view').length)
        //     $('.cloud-zoom').data('zoom').destroy();

        $('.more-views ul>li').removeClass('active');
        $(this).parent().addClass('active');

        dataimg = $(this).attr('dataimg');
        dataimgmain = $(this).attr('dataimgmain');
        datalabel = $(this).attr('title');
        
        $('.product-image-normal>a').attr('href', dataimg);
        $('.product-image-normal>a>img').attr('src', dataimgmain);
        $('.image-normal>a>img').attr('src', dataimgmain);
        $('.product-image .imageCaption').html(datalabel);
        $('.product-image a.fancybox').attr('title',datalabel);
        $('.projects-view-project .image-normal a.fancybox').attr('href', dataimg);
        //update counter
        var imageIndex =  $(this).parent().index();
        $('.product-view .counter span, .projects-view-project .counter span').text(imageIndex + 1);

       //create zoom again
        // if($('.catalog-product-view').length)
        //     $('.cloud-zoom, .cloud-zoom-gallery').CloudZoom();

        function showHideGalleryArrows(){
            var currentIndex = $('.more-views ul li.active').index();
            var length = $('.more-views ul li').length;

            if(currentIndex == length-1)
            {
                $('.nextImage').css('display','none');
            }
            else
            {
                $('.nextImage').css('display','block');
            }
            if(currentIndex == 0)
            {
                $('.prevImage').css('display','none');
            }
            else
            {
                $('.prevImage').css('display','block');
            }
        }
        showHideGalleryArrows();
        
    });


    $('.image-normal a, .product-image-normal a').on('click',function(){
        var dataindex = $(this).attr('data-index'); 
        var src = $(this).attr('href');
        var title = $(this).attr('title');

        $('body').append('<div class="fancyboxOverlay"><div class="fancyboxInner"><span class="loader"></span><span class="arrowLeft"></span><span class="arrowRight"></span><span class="close"></span><img alt="" src="'+src+'" /><span class="title">'+title+'</span></div></div>');
        $('html').addClass('fancybox-lock');

        correctImageSize();
        nextPrevImages();
        removeFancybox();
        return false;
    });
    function removeFancybox(){
        $('.fancyboxOverlay .fancyboxInner span.close').on('click',function(){
            $('.fancyboxOverlay').remove();
            $('html').removeClass('fancybox-lock');
        });
    }
    function nextPrevImages(){
        $('.fancyboxOverlay .fancyboxInner .arrowRight').on('click',function(){
            var index = $('.more-views ul li.active').index();
    
            var length = $('.more-views ul li').length;
            index++
            if(index == length)
                index = 0;

            index = checkNextIfVideo(index);

            $('a', $('.more-views ul li:eq('+index+')')).click();
            $('.fancyboxOverlay .loader').css('display', 'block');
            var src = $('.image-normal a, .product-image-normal a').attr('href');
            var title = $('.image-normal a, .product-image-normal a').attr('title');
            $('.fancyboxOverlay .fancyboxInner img').attr('src', src).one("load",function(){
                $('.fancyboxOverlay .loader').css('display', 'none');
            });
            $('.fancyboxOverlay .fancyboxInner .title').html(title);
            
            correctImageSize();
        });
        $('.fancyboxOverlay .fancyboxInner .arrowLeft').on('click',function(){
            var index = $('.more-views ul li.active').index();
            index--;

            index = checkPrevIfVideo(index);

            $('a', $('.more-views ul li:eq('+index+')')).click();
            $('.fancyboxOverlay .loader').css('display', 'block');
            var src = $('.image-normal a, .product-image-normal a').attr('href');
            var title = $('.image-normal a, .product-image-normal a').attr('title');
            $('.fancyboxOverlay .fancyboxInner img').attr('src', src).one("load",function(){
                $('.fancyboxOverlay .loader').css('display', 'none');
            });
            $('.fancyboxOverlay .fancyboxInner .title').html(title);
            correctImageSize();
        });
    }
    function correctImageSize(){
        $(".fancyboxOverlay .fancyboxInner img").load(function(){
            var windowHeight = $( window ).height();
            var windowWidth = $( window ).width();
            var imageHeight = $('.fancyboxOverlay .fancyboxInner img').height();
            var imageWidth = $('.fancyboxOverlay .fancyboxInner img').width();
            
            if(imageHeight > windowHeight){
                $('.fancyboxOverlay .fancyboxInner img').css('height',windowHeight-80+'px');
                $('.fancyboxOverlay .fancyboxInner img').css('width','auto');
            }
            
        });
    
    }
    function checkNextIfVideo(index){
        if($('.more-views ul li:eq('+index+')').hasClass('video'))
        {
            index++;
            index = checkNextIfVideo(index);
            return index;
            
        }
        else
        {
            return index;
        }
    }
    function checkPrevIfVideo(index){
        if($('.more-views ul li:eq('+index+')').hasClass('video'))
        {
            index--;
            index = checkNextIfVideo(index);
            return index;
            
        }
        else
        {
            return index;
        }
    }

    /* END FANCYBOX
    ********************/

    $('.more-views .navi .right').on('click',function(){
        var countItems = $('.more-views-inner ul li').length;
        var marginLeft = $('.more-views-inner ul').css('margin-left');
        var widthItem = $('.more-views-inner ul li').width();
        if(parseInt(marginLeft) > 0)
            var totalMarginLeft = 0;
        else
            var totalMarginLeft = Math.abs(parseInt(marginLeft)) + widthItem + 11;
        var widthContainer = $('.more-views-inner').width();
        
        if(((countItems+3)*widthItem-widthContainer)>Math.abs(parseInt(marginLeft)))
        {
            $('.more-views-inner ul').animate({
                'marginLeft': -totalMarginLeft
            },200);
        }
    });

    $('.more-views .navi .left').on('click',function(){
        var countItems = $('.more-views-inner ul li').length;
        var marginLeft = $('.more-views-inner ul').css('margin-left');
        var widthItem = $('.more-views-inner ul li').width();
        var totalMarginLeft = Math.abs(parseInt(marginLeft)) - widthItem - 11;
        var widthContainer = $('.more-views-inner').width();
     
                if(parseInt(marginLeft) < 0)
                {
                    $('.more-views-inner ul').animate({
                        'marginLeft': -totalMarginLeft
                    },200);
                }
                else
                {
                    $('.more-views-inner ul').animate({
                        'marginLeft': 0
                    },200);
                }
               
            
        
    });
    function removeArrows(){
        var widthContainer = $('.more-views-inner').width();
        var widthItem = $('.more-views-inner ul li').width();
        var countItems = $('.more-views-inner ul li').length;
        var widthElements = (widthItem + 10) * countItems;
        if(widthElements < widthContainer){
            $('.product-img-box .navi').css('display','none');
        }
        else
            $('.product-img-box .navi').css('display','block');
        //console.log(widthContainer+'+'+widthElements);
    }
    removeArrows()
    $( window ).resize(function() {
        removeArrows();
        correctImageSize();
    });


    $('.product-tabs-container .product_tabs').on('click',function(){
        var tabname = $(this).attr('id');
        $('.product-tabs-container .product_tabs').removeClass('active');
        $(this).addClass('active');
        $('.product-tabs-container .tabs-content').css('display','none');
        $('#'+tabname+'_content').css('display','block');
        return false;
    });
    function showHideArrow()
    {
        if($('ul.imagesSpecs').length)
        {
            var activeElem = $('ul.imagesSpecs li.active');
            var index = activeElem.index();
            var countItems = $('ul.imagesSpecs li').length;

            if(index == 0)
                $('.imagesSpecsWrap .navi .left').css('display','none');
            else
                $('.imagesSpecsWrap .navi .left').css('display','block');
            if(index == countItems-1)
                $('.imagesSpecsWrap .navi .right').css('display','none');
            else
                $('.imagesSpecsWrap .navi .right').css('display','block');
        }
    }
    showHideArrow();
    $('.imagesSpecsWrap .navi .right').on('click',function(){

        var activeElem = $('ul.imagesSpecs li.active');
        $('ul.imagesSpecs li').removeClass('active');
        activeElem.next().addClass('active');
        showHideArrow();

    });
    $('.imagesSpecsWrap .navi .left').on('click',function(){

        var activeElem = $('ul.imagesSpecs li.active');
        $('ul.imagesSpecs li').removeClass('active');
        activeElem.prev().addClass('active');
        showHideArrow();

    });

    $('.mobileMenuButton').on('click',function(){
        $('.main-menu').toggleClass('active');
        $(this).toggleClass('active');
    });

    $('.footerInner .bfm-nb-nav').on('click',function(){
        $(this).toggleClass('opened');
    });

    //product gallery
    function showHideGalleryArrows(){
        var currentIndex = $('.more-views ul li.active').index();
        var length = $('.more-views ul li').length;

        if(currentIndex == length-1)
        {
            $('.nextImage').css('display','none');
        }
        else
        {
            $('.nextImage').css('display','block');
        }
        if(currentIndex == 0)
        {
            $('.prevImage').css('display','none');
        }
        else
        {
            $('.prevImage').css('display','block');
        }
    }
    showHideGalleryArrows();
    
    $('.nextImage').on('click',function(){
        var nextImage = $('.more-views ul li.active').next();
        $('a',nextImage).click();
        showHideGalleryArrows();
    });

    $('.prevImage').on('click',function(){
        var prevImage = $('.more-views ul li.active').prev();
        $('a',prevImage).click();
        showHideGalleryArrows();
        
    });

    $('.catalog-product-view .arrowsAmount .less').on('click',function(){
        var quantity = $('.add-to-cart .qty').val();
        if(quantity != 1)
            quantity--;
        $('.add-to-cart .qty').val(quantity);
    });
    $('.catalog-product-view .arrowsAmount .more').on('click',function(){
        var quantity = $('.add-to-cart .qty').val();
        quantity++;
        $('.add-to-cart .qty').val(quantity);
    });

    //fix bug with not updating qty
    $('.add-to-cart .qty').on('change',function(){
        $('.add-to-cart .qty').val($(this).val());
    });

    $('.topBarLinks li.bulkOrder').on('click', function(){
        $('.bulkOrderForm').toggleClass('opened');

        return false;
    });

    $('.bulkOrderForm .addItem').on('click',function(){
        appendBulkOrderItem();
    });
    function appendBulkOrderItem(){
        $('.bulkOrderForm .rows').append('<div class="row"><input class="sku" type="text" name="sku[]" placeholder="SKU"/><input class="qty" type="text" name="qty[]" placeholder="QTY"/><span class="remove"></span><div class="clear"></div></div>');
        appendOnFocusOut();
        hideRemoveButton();
        removeBulkOrderItem();
    }
    function removeBulkOrderItem(){
        $('.bulkOrderForm .remove').on('click',function(){
            $(this).parent().remove();
            hideRemoveButton();
        });
    }
    removeBulkOrderItem();

    function hideRemoveButton(){
        var length = $('.bulkOrderForm .row').length;
        $('.bulkOrderForm .row .remove').css('display','block');
        if(length == 1)
            $('.bulkOrderForm .row:first-child .remove').css('display','none');
    }

    function appendOnFocusOut(){
        $('.bulkOrderForm .row .sku').last().focusout(function(){
            if($(this).val() !== ''){
                $(this).unbind( "focusout");
                appendBulkOrderItem();
            }
            hideRemoveButton();

        });
    }
    appendOnFocusOut();
    $('.bulkOrderForm input[type="submit"]').on('click',function(){
            $('.bulkOrderLoader').css('display','inline-block');
            var i = 0;
            var data = $(".bulkOrderForm form").serializeArray();
            
            //check if not empty

            var flag = true;
            $('.bulkOrderForm .rows .row .error').remove();
            $('.bulkOrderForm .rows .row').each(function(index){
                var val = $('input.sku',$(this)).val();
                if(val == "")
                {

                    if(index > 0)
                        $(this).remove();
                    else{
                        $(this).append("<span class='error'>The field is empty.</span>");
                        flag = false;
                        $('.bulkOrderLoader').css('display','none');
                    }
                }

            });

            var url = '/bulk-order.php';

            if(flag)
            {
                $.ajax({
                    url: url,
                    type: 'post',
                    data: data,
                    success: function (d) {
                        if(d != 'ok')
                        {
                             
                            
                            $('.bulkOrderForm .rows .row .error').remove();
                                arr = d.split(','),
                                i;
                            for(x=0; x<arr.length; x++){
                                var item = arr[x].split('#!@');
                                if(item[0] == 'noexist')
                                    $('.bulkOrderForm .rows .row').eq(item[1]).append("<span class='error'>The product doesn't exist.</span>"); 
                                if(item[0] == 'configurable')
                                    $('.bulkOrderForm .rows .row').eq(item[1]).append('<span class="error">This is a configurable product. Please <a target="_blank" href="'+item[2]+'">click here</a> to configure it and use the configured part number to do bulk ordering.</span>'); 
                                if(item[0] == 'outofstock')
                                    $('.bulkOrderForm .rows .row').eq(item[1]).append("<span class='error'>The product is currently out of stock.</span>"); 
                                if(item[0] == 'redirect')
                                    $('.bulkOrderForm .rows .row').eq(item[1]).append("<span class='error'>The product doesn't exist.</span>");
                            }
                            $('.bulkOrderLoader').css('display','none');

                        }
                        else{
                            window.location = '/checkout/cart/';
                        }
                          
                    }
                }); 
            }
              

        return false;
    });

    $('.tabsWrap .activeElem').on('click',function(){
        $('.projects-index-index .tabsMenu').toggleClass('opened');
    });


    //if !specs & !downloads & !techtips
    if(!$('#tab_specs').length && !$('#tab_downloads').length && !$('#tab_techtips').length)
    {
        $('#tab_projects').css('left', '-1px');
        $('#tab_projects').addClass('active');
        $('#tab_projects_content').css('display','block');  
    }
    //if !specs & !downloads
    else if(!$('#tab_specs').length && !$('#tab_downloads').length)
    {
        $('#tab_techtips').addClass('active');
        $('#tab_techtips_content').css('display','block');
        $('#tab_techtips').css('left', '-1px');
        $('#tab_projects').css('left', '176px');
    }
     //if !specs & !techtips
    else if(!$('#tab_specs').length && !$('#tab_techtips').length)
    {
        $('#tab_downloads').css('left', '-1px');
        $('#tab_projects').css('left', '199px');
        $('#tab_downloads').addClass('active');
        $('#tab_downloads_content').css('display','block');
    }
    //if !downloads & !techtips
    else if(!$('#tab_downloads').length && !$('#tab_techtips').length)
    {
        $('#tab_projects').css('left', '140px');
    }
    //if !specs
    else if(!$('#tab_specs').length)
    {
        $('#tab_downloads').css('left', '-1px');
        $('#tab_downloads').addClass('active');
        $('#tab_downloads_content').css('display','block');
        $('#tab_techtips').css('left', '199px');
        $('#tab_projects').css('left', '376px');
    }
    //if !downloads
    else if(!$('#tab_downloads').length)
    {
        $('#tab_techtips').css('left', '140px');
        $('#tab_projects').css('left', '317px');
    }
    //if !techtips
    else if(!$('#tab_techtips').length)
    {
        $('#tab_projects').css('left', '340px');  
    }



    //*****Check if a link is external, if so, add target ="_blank"
    //******************************************************************/
    hostname = new RegExp(location.host);
    servocity1 = new RegExp('http://servocity');
    servocity2 = new RegExp('http://www.servocity');
    servocity3 = new RegExp('javacript');
    $('.col-main a').each(function(){
        var hrefAttr = $(this).attr('href');
        if(typeof hrefAttr != 'undefined'){
            if(!hostname.test(hrefAttr) && !servocity1.test(hrefAttr) && !servocity2.test(hrefAttr) && hrefAttr.slice(0,1) != '/' && hrefAttr.slice(0,1) != '#'){
                if(servocity3.test(hrefAttr))
                    $(this).attr('target','_blank')
            }
        }
    });


    //remove breadcrumb

    var numberBreadcrumbs = $('.catalog-product-view .breadcrumbs ul li').length;
    if(numberBreadcrumbs < 3 && $('.catalog-product-view .breadcrumbs ul li:nth-child(2)').hasClass('product'))
    {
        $('.catalog-product-view .breadcrumbs').css('display','none');
    }
    
    var href = window.location.href;
    if($('.product-essential .price-box .priceRange').length > 0 && href.indexOf('#') <= -1)
    {
        $('.price-box .regular-price > .price,.price-box .old-price, .price-box .special-price').css('display','none');
        $('.priceRange').css('display','block');
    }

    function checkIfOptionsSelected(){
        var flag = "";
        $('.catalog-product-view #product-options-wrapper dl .row').each(function(){
            var selectValue = $('dd div select',$(this)).val();
            if(!IsNumeric(selectValue) || selectValue == "")
                flag += 'false';
        });
        if(flag.indexOf('false') <= -1)
        {
            $('.price-box .regular-price > .price,.price-box .old-price, .price-box .special-price').css('display','block');
            $('.price-box .priceRange').css('display','none');
        }
        else
        {
            if($('.product-shop .price-box .priceRange').length){
                $('.price-box .regular-price > .price,.price-box .old-price, .price-box .special-price').css('display','none');
                $('.price-box .priceRange').css('display','block');
            }
            else
                $('.price-box .regular-price > .price,.price-box .old-price, .price-box .special-price').css('display','block');
        }
    }
    function IsNumeric(input){
        var RE = /^-{0,1}\d*\.{0,1}\d+$/;
        return (RE.test(input));
    }
    checkIfOptionsSelected();

    $('.catalog-product-view #product-options-wrapper dl .row select').on('change',function(){
         checkIfOptionsSelected();
    });
});
