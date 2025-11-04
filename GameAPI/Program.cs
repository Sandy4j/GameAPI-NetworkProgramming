using GameAPI.Data;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllers();     // Registrasi controller (MVC tanpa view)
builder.Services.AddEndpointsApiExplorer();   // Untuk OpenAPI
builder.Services.AddSwaggerGen();   // Generator dokumentasi Swagger

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowAll", policy =>
    {
        policy.AllowAnyOrigin()
            .AllowAnyMethod()
   .AllowAnyHeader();
    });
});

builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseSqlite(builder.Configuration.GetConnectionString("DefaultConnection"))
); // DI: AppDbContext menggunakan SQLite

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();       // Serve dok OpenAPI (JSON)
    app.UseSwaggerUI();     // UI interaktif untuk uji endpoint
}

app.UseHttpsRedirection();  // Redirect HTTP -> HTTPS saat Development

// Gunakan CORS policy
app.UseCors("AllowAll");

app.UseAuthorization();   // Middleware otorisasi (siap untuk JWT nanti)
app.MapControllers();       // Pemetaan attribute routing controller

app.Run();
