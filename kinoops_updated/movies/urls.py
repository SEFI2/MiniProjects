from django.conf.urls import url, include
from . import views
urlpatterns = [
    url(r'^$' , views.home_page, name='home_page'),
    url(r'^(?P<filter_type>[^/]+)/(?P<filters>[^/]+)/$', views.movie_list , name='movie_list'),

]
