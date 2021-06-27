using SGSE.Models;
using SGSE.Repositories;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SGSE.Services
{
    public class InvoiceService : IInvoiceService
    {
        private readonly IInvoiceRepository _repository;

        public InvoiceService(IInvoiceRepository repository)
        {
            _repository = repository;
        }
        public Task<Invoice> Create(Invoice invoice)
        {
            var createdInvoice = _repository.Create(invoice);
            
            throw new NotImplementedException();
        }

        public Task<List<Invoice>> GetAll()
        {
            throw new NotImplementedException();
        }

        public Task<Invoice> GetById(string id)
        {
            throw new NotImplementedException();
        }

        public Task Remove(Invoice invoice)
        {
            throw new NotImplementedException();
        }

        public Task RemoveById(string id)
        {
            throw new NotImplementedException();
        }

        public Task Update(string id, Invoice invoice)
        {
            throw new NotImplementedException();
        }
    }
}
