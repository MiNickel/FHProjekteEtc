using MongoDB.Driver;
using SGSE.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SGSE.Repositories
{
    public class InvoiceRepository : IInvoiceRepository
    {
        private readonly IMongoCollection<Invoice> _invoices;

        public InvoiceRepository(IInvoiceDatabaseSettings settings)
        {
            var client = new MongoClient(settings.ConnectionString);
            var database = client.GetDatabase(settings.DatabaseName);

            _invoices = database.GetCollection<Invoice>(settings.InvoiceCollectionName);
        }

        public List<Invoice> GetAll() =>
            _invoices.Find(Invoice => true).ToList();

        public Invoice GetById(string id) =>
            _invoices.Find(Invoice => Invoice.Id == id).FirstOrDefault();

        public Invoice Create(Invoice Invoice)
        {
            _invoices.InsertOne(Invoice);
            return Invoice;
        }

        public void Update(string id, Invoice InvoiceIn) =>
            _invoices.ReplaceOne(Invoice => Invoice.Id == id, InvoiceIn);

        public void Remove(Invoice InvoiceIn) =>
            _invoices.DeleteOne(Invoice => Invoice.Id == InvoiceIn.Id);

        public void RemoveById(string id) =>
            _invoices.DeleteOne(Invoice => Invoice.Id == id);
    }
}
