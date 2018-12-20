from django.contrib import admin
from . import models


# Register your models here.
admin.site.register(models.Movie)
admin.site.register(models.Genre)
admin.site.register(models.Country)
admin.site.register(models.Category)
admin.site.register(models.Director)
admin.site.register(models.Actor)
admin.site.register(models.Link)
admin.site.register(models.MovieWebsite)






