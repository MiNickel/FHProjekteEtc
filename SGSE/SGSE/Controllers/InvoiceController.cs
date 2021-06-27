using Microsoft.AspNetCore.Mvc;
using SGSE.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace SGSE.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class InvoiceController : ControllerBase
    {
        private readonly IInvoiceService _service;

        public InvoiceController(IInvoiceService service)
        {
            _service = service;
        }
        // GET: api/<InvoiceController>
        [HttpGet]
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET api/<InvoiceController>/5
        [HttpGet("{id}")]
        public string Get(int id)
        {
            _service.Create(null);
            return "value";
        }

        // POST api/<InvoiceController>
        [HttpPost]
        public void Post([FromBody] string value)
        {
            Console.WriteLine("asdasd");
            
        }

        // PUT api/<InvoiceController>/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE api/<InvoiceController>/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
