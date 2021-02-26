/** Copyright Text */
package org.snmp4j.agent.tutorial;
// --AgentGen BEGIN=_BEGIN
// --AgentGen END

import org.snmp4j.smi.*;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.agent.*;
import org.snmp4j.agent.mo.*;
import org.snmp4j.agent.mo.snmp.*;
import org.snmp4j.agent.mo.snmp.smi.*;
import org.snmp4j.agent.request.*;
import org.snmp4j.log.LogFactory;
import org.snmp4j.log.LogAdapter;
import org.snmp4j.agent.mo.snmp.tc.*;

// --AgentGen BEGIN=_IMPORT
// --AgentGen END

public class GrEventsMib
        // --AgentGen BEGIN=_EXTENDS
        // --AgentGen END
        implements MOGroup
// --AgentGen BEGIN=_IMPLEMENTS
// --AgentGen END
{

    private static final LogAdapter LOGGER = LogFactory.getLogger(GrEventsMib.class);

    // --AgentGen BEGIN=_STATIC
    // --AgentGen END

    // Factory
    private MOFactory moFactory = DefaultMOFactory.getInstance();

    // Constants

    /** OID of this MIB module for usage which can be used for its identification. */
    public static final OID oidGrEventsMib = new OID(new int[] {1, 3, 6, 1, 4, 1, 2424});

    // Identities
    // Scalars
    public static final OID oidGrMIBTotalEvents = new OID(new int[] {1, 3, 6, 1, 4, 1, 2424, 4, 0});
    // Tables

    // Notifications

    // Enumerations

    // TextualConventions

    // Scalars
    private MOScalar<Counter32> grMIBTotalEvents;

    // Tables
    public static final OID oidGrMIBEventsEntry = new OID(new int[] {1, 3, 6, 1, 4, 1, 2424, 5, 1});

    // Index OID definitions
    public static final OID oidGrMIBEventsIndex =
            new OID(new int[] {1, 3, 6, 1, 4, 1, 2424, 5, 1, 1});

    // Column TC definitions for grMIBEventsEntry:

    // Column sub-identifier definitions for grMIBEventsEntry:
    public static final int colGrMIBEventsIndex = 1;
    public static final int colGrMIBEventsNome = 2;
    public static final int colGrMIBEventsAno = 3;
    public static final int colGrMIBEventsMes = 4;
    public static final int colGrMIBEventsDia = 5;
    public static final int colGrMIBEventsHora = 6;
    public static final int colGrMIBEventsMinutos = 7;
    public static final int colGrMIBEventsMensagem = 8;
    public static final int colGrMIBEventsValidade = 9;

    // Column index definitions for grMIBEventsEntry:
    public static final int idxGrMIBEventsIndex = 0;
    public static final int idxGrMIBEventsNome = 1;
    public static final int idxGrMIBEventsAno = 2;
    public static final int idxGrMIBEventsMes = 3;
    public static final int idxGrMIBEventsDia = 4;
    public static final int idxGrMIBEventsHora = 5;
    public static final int idxGrMIBEventsMinutos = 6;
    public static final int idxGrMIBEventsMensagem = 7;
    public static final int idxGrMIBEventsValidade = 8;

    private MOTableSubIndex[] grMIBEventsEntryIndexes;
    private MOTableIndex grMIBEventsEntryIndex;

    @SuppressWarnings(value = {"rawtypes"})
    private MOTable<GrMIBEventsEntryRow, MOColumn, MOTableModel<GrMIBEventsEntryRow>>
            grMIBEventsEntry;

    private MOTableModel<GrMIBEventsEntryRow> grMIBEventsEntryModel;

    // --AgentGen BEGIN=_MEMBERS
    // --AgentGen END

    /**
     * Constructs a GrEventsMib instance without actually creating its <code>ManagedObject</code>
     * instances. This has to be done in a sub-class constructor or after construction by calling
     * {@link #createMO(MOFactory moFactory)}.
     */
    protected GrEventsMib() {
        // --AgentGen BEGIN=_DEFAULTCONSTRUCTOR
        // --AgentGen END
    }

    /**
     * Constructs a GrEventsMib instance and actually creates its <code>ManagedObject</code>
     * instances using the supplied <code>MOFactory</code> (by calling {@link #createMO(MOFactory
     * moFactory)}).
     *
     * @param moFactory the <code>MOFactory</code> to be used to create the managed objects for this
     *     module.
     */
    public GrEventsMib(MOFactory moFactory) {
        this();
        // --AgentGen BEGIN=_FACTORYCONSTRUCTOR::factoryWrapper
        // --AgentGen END
        this.moFactory = moFactory;
        createMO(moFactory);
        // --AgentGen BEGIN=_FACTORYCONSTRUCTOR
        // --AgentGen END
    }

    // --AgentGen BEGIN=_CONSTRUCTORS
    // --AgentGen END

    /**
     * Create the ManagedObjects defined for this MIB module using the specified {@link MOFactory}.
     *
     * @param moFactory the <code>MOFactory</code> instance to use for object creation.
     */
    protected void createMO(MOFactory moFactory) {
        addTCsToFactory(moFactory);
        grMIBTotalEvents =
                moFactory.createScalar(
                        oidGrMIBTotalEvents,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
                        new Counter32());
        createGrMIBEventsEntry(moFactory);
    }

    public MOScalar<Counter32> getGrMIBTotalEvents() {
        return grMIBTotalEvents;
    }

    @SuppressWarnings(value = {"rawtypes"})
    public MOTable<GrMIBEventsEntryRow, MOColumn, MOTableModel<GrMIBEventsEntryRow>>
            getGrMIBEventsEntry() {
        return grMIBEventsEntry;
    }

    @SuppressWarnings(value = {"unchecked"})
    private void createGrMIBEventsEntry(MOFactory moFactory) {
        // Index definition
        grMIBEventsEntryIndexes =
                new MOTableSubIndex[] {
                    moFactory.createSubIndex(oidGrMIBEventsIndex, SMIConstants.SYNTAX_INTEGER, 1, 1)
                };

        grMIBEventsEntryIndex =
                moFactory.createIndex(
                        grMIBEventsEntryIndexes,
                        false,
                        new MOTableIndexValidator() {
                            public boolean isValidIndex(OID index) {
                                boolean isValidIndex = true;
                                // --AgentGen BEGIN=grMIBEventsEntry::isValidIndex
                                // --AgentGen END
                                return isValidIndex;
                            }
                        });

        // Columns
        MOColumn<?>[] grMIBEventsEntryColumns = new MOColumn<?>[9];
        grMIBEventsEntryColumns[idxGrMIBEventsIndex] =
                moFactory.createColumn(
                        colGrMIBEventsIndex,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
        grMIBEventsEntryColumns[idxGrMIBEventsNome] =
                moFactory.createColumn(
                        colGrMIBEventsNome,
                        SMIConstants.SYNTAX_OCTET_STRING,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
        grMIBEventsEntryColumns[idxGrMIBEventsAno] =
                new MOMutableColumn<Integer32>(
                        colGrMIBEventsAno,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE),
                        (Integer32) null
                        // --AgentGen BEGIN=grMIBEventsAno::auxInit
                        // --AgentGen END
                        );
        ((MOMutableColumn<?>) grMIBEventsEntryColumns[idxGrMIBEventsAno])
                .addMOValueValidationListener(new GrMIBEventsAnoValidator());
        grMIBEventsEntryColumns[idxGrMIBEventsMes] =
                new MOMutableColumn<Integer32>(
                        colGrMIBEventsMes,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE),
                        (Integer32) null
                        // --AgentGen BEGIN=grMIBEventsMes::auxInit
                        // --AgentGen END
                        );
        ((MOMutableColumn<?>) grMIBEventsEntryColumns[idxGrMIBEventsMes])
                .addMOValueValidationListener(new GrMIBEventsMesValidator());
        grMIBEventsEntryColumns[idxGrMIBEventsDia] =
                new MOMutableColumn<Integer32>(
                        colGrMIBEventsDia,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE),
                        (Integer32) null
                        // --AgentGen BEGIN=grMIBEventsDia::auxInit
                        // --AgentGen END
                        );
        ((MOMutableColumn<?>) grMIBEventsEntryColumns[idxGrMIBEventsDia])
                .addMOValueValidationListener(new GrMIBEventsDiaValidator());
        grMIBEventsEntryColumns[idxGrMIBEventsHora] =
                new MOMutableColumn<Integer32>(
                        colGrMIBEventsHora,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE),
                        (Integer32) null
                        // --AgentGen BEGIN=grMIBEventsHora::auxInit
                        // --AgentGen END
                        );
        ((MOMutableColumn<?>) grMIBEventsEntryColumns[idxGrMIBEventsHora])
                .addMOValueValidationListener(new GrMIBEventsHoraValidator());
        grMIBEventsEntryColumns[idxGrMIBEventsMinutos] =
                new MOMutableColumn<Integer32>(
                        colGrMIBEventsMinutos,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE),
                        (Integer32) null
                        // --AgentGen BEGIN=grMIBEventsMinutos::auxInit
                        // --AgentGen END
                        );
        ((MOMutableColumn<?>) grMIBEventsEntryColumns[idxGrMIBEventsMinutos])
                .addMOValueValidationListener(new GrMIBEventsMinutosValidator());
        grMIBEventsEntryColumns[idxGrMIBEventsMensagem] =
                new MOMutableColumn<OctetString>(
                        colGrMIBEventsMensagem,
                        SMIConstants.SYNTAX_OCTET_STRING,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE),
                        (OctetString) null
                        // --AgentGen BEGIN=grMIBEventsMensagem::auxInit
                        // --AgentGen END
                        );
        ((MOMutableColumn<?>) grMIBEventsEntryColumns[idxGrMIBEventsMensagem])
                .addMOValueValidationListener(new GrMIBEventsMensagemValidator());
        grMIBEventsEntryColumns[idxGrMIBEventsValidade] =
                moFactory.createColumn(
                        colGrMIBEventsValidade,
                        SMIConstants.SYNTAX_OCTET_STRING,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
        // Table model
        grMIBEventsEntryModel =
                moFactory.createTableModel(
                        oidGrMIBEventsEntry, grMIBEventsEntryIndex, grMIBEventsEntryColumns);
        ((MOMutableTableModel<GrMIBEventsEntryRow>) grMIBEventsEntryModel)
                .setRowFactory(new GrMIBEventsEntryRowFactory());
        grMIBEventsEntry =
                moFactory.createTable(
                        oidGrMIBEventsEntry,
                        grMIBEventsEntryIndex,
                        grMIBEventsEntryColumns,
                        grMIBEventsEntryModel);
    }

    public void registerMOs(MOServer server, OctetString context)
            throws DuplicateRegistrationException {
        // Scalar Objects
        server.register(this.grMIBTotalEvents, context);
        server.register(this.grMIBEventsEntry, context);
        // --AgentGen BEGIN=_registerMOs
        // --AgentGen END
    }

    public void unregisterMOs(MOServer server, OctetString context) {
        // Scalar Objects
        server.unregister(this.grMIBTotalEvents, context);
        server.unregister(this.grMIBEventsEntry, context);
        // --AgentGen BEGIN=_unregisterMOs
        // --AgentGen END
    }

    // Notifications

    // Scalars

    // Value Validators

    /**
     * The <code>GrMIBEventsAnoValidator</code> implements the value validation for <code>
     * GrMIBEventsAno</code>.
     */
    static class GrMIBEventsAnoValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            // --AgentGen BEGIN=grMIBEventsAno::validate
            // --AgentGen END
        }
    }
    /**
     * The <code>GrMIBEventsMesValidator</code> implements the value validation for <code>
     * GrMIBEventsMes</code>.
     */
    static class GrMIBEventsMesValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            // --AgentGen BEGIN=grMIBEventsMes::validate
            // --AgentGen END
        }
    }
    /**
     * The <code>GrMIBEventsDiaValidator</code> implements the value validation for <code>
     * GrMIBEventsDia</code>.
     */
    static class GrMIBEventsDiaValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            // --AgentGen BEGIN=grMIBEventsDia::validate
            // --AgentGen END
        }
    }
    /**
     * The <code>GrMIBEventsHoraValidator</code> implements the value validation for <code>
     * GrMIBEventsHora</code>.
     */
    static class GrMIBEventsHoraValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            // --AgentGen BEGIN=grMIBEventsHora::validate
            // --AgentGen END
        }
    }
    /**
     * The <code>GrMIBEventsMinutosValidator</code> implements the value validation for <code>
     * GrMIBEventsMinutos</code>.
     */
    static class GrMIBEventsMinutosValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            // --AgentGen BEGIN=grMIBEventsMinutos::validate
            // --AgentGen END
        }
    }
    /**
     * The <code>GrMIBEventsMensagemValidator</code> implements the value validation for <code>
     * GrMIBEventsMensagem</code>.
     */
    static class GrMIBEventsMensagemValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            // --AgentGen BEGIN=grMIBEventsMensagem::validate
            // --AgentGen END
        }
    }

    // Rows and Factories

    public class GrMIBEventsEntryRow extends DefaultMOMutableRow2PC {

        // --AgentGen BEGIN=grMIBEventsEntry::RowMembers
        // --AgentGen END

        public GrMIBEventsEntryRow(OID index, Variable[] values) {
            super(index, values);
            // --AgentGen BEGIN=grMIBEventsEntry::RowConstructor
            // --AgentGen END
        }

        public Integer32 getGrMIBEventsIndex() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsIndex
            // --AgentGen END
            return (Integer32) super.getValue(idxGrMIBEventsIndex);
        }

        public void setGrMIBEventsIndex(Integer32 newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsIndex
            // --AgentGen END
            super.setValue(idxGrMIBEventsIndex, newColValue);
        }

        public OctetString getGrMIBEventsNome() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsNome
            // --AgentGen END
            return (OctetString) super.getValue(idxGrMIBEventsNome);
        }

        public void setGrMIBEventsNome(OctetString newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsNome
            // --AgentGen END
            super.setValue(idxGrMIBEventsNome, newColValue);
        }

        public Integer32 getGrMIBEventsAno() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsAno
            // --AgentGen END
            return (Integer32) super.getValue(idxGrMIBEventsAno);
        }

        public void setGrMIBEventsAno(Integer32 newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsAno
            // --AgentGen END
            super.setValue(idxGrMIBEventsAno, newColValue);
        }

        public Integer32 getGrMIBEventsMes() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsMes
            // --AgentGen END
            return (Integer32) super.getValue(idxGrMIBEventsMes);
        }

        public void setGrMIBEventsMes(Integer32 newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsMes
            // --AgentGen END
            super.setValue(idxGrMIBEventsMes, newColValue);
        }

        public Integer32 getGrMIBEventsDia() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsDia
            // --AgentGen END
            return (Integer32) super.getValue(idxGrMIBEventsDia);
        }

        public void setGrMIBEventsDia(Integer32 newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsDia
            // --AgentGen END
            super.setValue(idxGrMIBEventsDia, newColValue);
        }

        public Integer32 getGrMIBEventsHora() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsHora
            // --AgentGen END
            return (Integer32) super.getValue(idxGrMIBEventsHora);
        }

        public void setGrMIBEventsHora(Integer32 newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsHora
            // --AgentGen END
            super.setValue(idxGrMIBEventsHora, newColValue);
        }

        public Integer32 getGrMIBEventsMinutos() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsMinutos
            // --AgentGen END
            return (Integer32) super.getValue(idxGrMIBEventsMinutos);
        }

        public void setGrMIBEventsMinutos(Integer32 newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsMinutos
            // --AgentGen END
            super.setValue(idxGrMIBEventsMinutos, newColValue);
        }

        public OctetString getGrMIBEventsMensagem() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsMensagem
            // --AgentGen END
            return (OctetString) super.getValue(idxGrMIBEventsMensagem);
        }

        public void setGrMIBEventsMensagem(OctetString newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsMensagem
            // --AgentGen END
            super.setValue(idxGrMIBEventsMensagem, newColValue);
        }

        public OctetString getGrMIBEventsValidade() {
            // --AgentGen BEGIN=grMIBEventsEntry::getGrMIBEventsValidade
            // --AgentGen END
            return (OctetString) super.getValue(idxGrMIBEventsValidade);
        }

        public void setGrMIBEventsValidade(OctetString newColValue) {
            // --AgentGen BEGIN=grMIBEventsEntry::setGrMIBEventsValidade
            // --AgentGen END
            super.setValue(idxGrMIBEventsValidade, newColValue);
        }

        public Variable getValue(int column) {
            // --AgentGen BEGIN=grMIBEventsEntry::RowGetValue
            // --AgentGen END
            switch (column) {
                case idxGrMIBEventsIndex:
                    return getGrMIBEventsIndex();
                case idxGrMIBEventsNome:
                    return getGrMIBEventsNome();
                case idxGrMIBEventsAno:
                    return getGrMIBEventsAno();
                case idxGrMIBEventsMes:
                    return getGrMIBEventsMes();
                case idxGrMIBEventsDia:
                    return getGrMIBEventsDia();
                case idxGrMIBEventsHora:
                    return getGrMIBEventsHora();
                case idxGrMIBEventsMinutos:
                    return getGrMIBEventsMinutos();
                case idxGrMIBEventsMensagem:
                    return getGrMIBEventsMensagem();
                case idxGrMIBEventsValidade:
                    return getGrMIBEventsValidade();
                default:
                    return super.getValue(column);
            }
        }

        public void setValue(int column, Variable value) {
            // --AgentGen BEGIN=grMIBEventsEntry::RowSetValue
            // --AgentGen END
            switch (column) {
                case idxGrMIBEventsIndex:
                    setGrMIBEventsIndex((Integer32) value);
                    break;
                case idxGrMIBEventsNome:
                    setGrMIBEventsNome((OctetString) value);
                    break;
                case idxGrMIBEventsAno:
                    setGrMIBEventsAno((Integer32) value);
                    break;
                case idxGrMIBEventsMes:
                    setGrMIBEventsMes((Integer32) value);
                    break;
                case idxGrMIBEventsDia:
                    setGrMIBEventsDia((Integer32) value);
                    break;
                case idxGrMIBEventsHora:
                    setGrMIBEventsHora((Integer32) value);
                    break;
                case idxGrMIBEventsMinutos:
                    setGrMIBEventsMinutos((Integer32) value);
                    break;
                case idxGrMIBEventsMensagem:
                    setGrMIBEventsMensagem((OctetString) value);
                    break;
                case idxGrMIBEventsValidade:
                    setGrMIBEventsValidade((OctetString) value);
                    break;
                default:
                    super.setValue(column, value);
            }
        }

        // --AgentGen BEGIN=grMIBEventsEntry::Row
        // --AgentGen END
    }

    public class GrMIBEventsEntryRowFactory implements MOTableRowFactory<GrMIBEventsEntryRow> {
        public synchronized GrMIBEventsEntryRow createRow(OID index, Variable[] values)
                throws UnsupportedOperationException {
            GrMIBEventsEntryRow row = new GrMIBEventsEntryRow(index, values);
            // --AgentGen BEGIN=grMIBEventsEntry::createRow
            // --AgentGen END
            return row;
        }

        public synchronized void freeRow(GrMIBEventsEntryRow row) {
            // --AgentGen BEGIN=grMIBEventsEntry::freeRow
            // --AgentGen END
        }

        // --AgentGen BEGIN=grMIBEventsEntry::RowFactory
        // --AgentGen END
    }

    // --AgentGen BEGIN=_METHODS
    // --AgentGen END

    // Textual Definitions of MIB module GrEventsMib
    protected void addTCsToFactory(MOFactory moFactory) {}

    // --AgentGen BEGIN=_TC_CLASSES_IMPORTED_MODULES_BEGIN
    // --AgentGen END

    // Textual Definitions of other MIB modules
    public void addImportedTCsToFactory(MOFactory moFactory) {}

    // --AgentGen BEGIN=_TC_CLASSES_IMPORTED_MODULES_END
    // --AgentGen END

    // --AgentGen BEGIN=_CLASSES
    // --AgentGen END

    // --AgentGen BEGIN=_END
    // --AgentGen END
}
